---
name: Bug report
about: Create a report to help us improve

---

**Describe the bug**
A clear and concise description of what the bug is.

**To Reproduce**
Steps to reproduce the behavior. Usually an actual failing command line command.

**Expected behavior**
A clear and concise description of what you expected to happen.

**Environment:**
 - OS and version: [e.g. CentOS 3]
 - **Megatools version!**

**Debug output**
 - Provide debug output by running the tool with --debug http,api
 - Sanitize it (remove session IDs, whatever other private info you want removed, etc.), or send it directly to megous@megous.com to avoid github.com. Most of the output is safe to be posted, except for session ids. Anyone can delete all your files, or cause some other mess just by knowing the session id.
 - Most of the debug output is already encrypted and useless on its own, without knowing the password. Alternatively, use an empty test account for debugging.

**Self help**
 - If error seems transient (error 509, ERATELIMIT, ...), wait a bit before reporting
 - Run megatools with --debug http,api and check if anything seems out of place (for CURL errors, certificate errors, API errors (EXXXXX), etc.)
 - Look through [recently closed issues](https://github.com/megous/megatools/issues?q=is%3Aissue+is%3Aclosed)
 - For compilation errors, if you're running an esoteric/old platform/OS, try to fix the error yourself and send the patch.
