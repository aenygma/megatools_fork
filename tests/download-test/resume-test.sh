#!/bin/sh

# use build binaries
export PATH="../..:$PATH"

set -e
make -C ../..

err()
{
	echo "FAIL: $@"
	exit 1
}

test_download()
{
	rm -f .tmp/test.dst
	megaget --path .tmp/test.dst /Root/.testfile || err "download failed: $1"
	cmp .tmp/test.src .tmp/test.dst || err "source != target post download: $1"
	echo "OK: $1"
}

prep_resume_file() # size
{
	cp .tmp/test.src ".tmp/.megatmp.$handle"
	truncate -s "$1" ".tmp/.megatmp.$handle"
}

del_resume_file()
{
	rm -f ".tmp/.megatmp.$handle"
}

prep_source_file()
{
	rm -rf .tmp
	mkdir -p .tmp

	dd if=/dev/urandom of=.tmp/test.src bs=1M count=66
	truncate -s "$1" .tmp/test.src

	megarm /Root/.testfile || true
	megaput --path /Root/.testfile .tmp/test.src
	handle=`megals -l /Root/.testfile | cut -d ' ' -f 1`
	egrep -e '^[a-zA-Z0-9]+$' <<< "$handle" || err "wut?"
}

i=0
while test $i -lt 6 ; do
	# create source file and upload it (make sure it is big and random sized)
	# make sure, we test 16byte alignment at least once
	test_size=$((1024*1024*64))
	test $i -eq 0 || test_size=$(($test_size + RANDOM))
	prep_source_file $test_size

	# download file without resume
	del_resume_file
	test_download "no resume, test_size=$test_size"
	
	prep_resume_file 0
	test_download "resume=0, test_size=$test_size"
	
	prep_resume_file $test_size
	test_download "resume=test_size, test_size=$test_size"

	# download file with varying resume offsets
	j=0
	while test $j -lt 7 ; do
		resume_size=$(($test_size - RANDOM - (RANDOM % 32 * 1024 * 1024)))
		test $j -eq 0 && resume_size=$(($resume_size - $resume_size % 16))
		prep_resume_file $resume_size
		test_download "resume=$resume_size, test_size=$test_size"
		j=$(($j+1))
	done

	i=$(($i+1))
done

