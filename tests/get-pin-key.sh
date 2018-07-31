#!/bin/sh

openssl s_client -servername g.api.mega.co.nz -connect g.api.mega.co.nz:443 < /dev/null | sed -n "/-----BEGIN/,/-----END/p" > cert.pem
openssl x509 -in cert.pem -pubkey -noout > pubkey.pem
openssl asn1parse -noout -inform pem -in pubkey.pem -out pubkey.der

echo -n "#define MEGA_NZ_API_PUBKEY_PIN \"sha256//"
openssl dgst -sha256 -binary pubkey.der | openssl base64 | tr --delete '\n'
echo "\""

rm -f *.pem *.der
