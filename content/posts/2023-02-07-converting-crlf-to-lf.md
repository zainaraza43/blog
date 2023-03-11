---
title: Converting CRLF Line Endings to LF in Linux
date: 2023-02-07
draft: false
---

Dealing with CRLF can be extremely annoying on Linux, as it can cause errors when attempting to execute scripts or compile files. It is especially problematic when working with text files that were created on Windows, as they are formatted differently than Linux. Fortunately, there are easy ways to fix this issue. Traditionally, this has been done by using the `dos2unix` command, which can quickly and easily convert Windows-formatted text files to Linux-formatted ones, allowing you to avoid the headache of dealing with CRLF. This, however, requires you to first install `dos2unix`, which you may not be able to do or may not want to do. In this case, you can use the built in `tr` command, as I'll show below.

## Using dos2unix

If you're willing and able to install a new program for this purpose, dos2unix is the simplest option. Simply install it (`sudo apt install dos2unix` on Debian-based systems) and then run it using `dos2unix myfile.txt`, where `myfile.txt` is the file you'd like to convert.

## Using tr

If you aren't able to install a new program (or don't want to), you can use the `tr` command to accomplish the same thing. Simply run the following to convert `myfile.txt`:

```sh
(tr -d '\r' < myfile.txt) > myfile.txt._temp && mv myfile.txt._temp myfile.txt
```

This script will read from myfile.txt, delete the CRLF characters, save the contents to myfile.txt._temp, then rename myfile.txt._temp to myfile.txt. In practice, it does the same thing as dos2unix.

If you don't want to manually type this for every file you want to convert, you can create a shell script and use variables. For example, you can save the following to a script called `crlftolf.sh`:

```sh
#!/bin/sh
(tr -d '\r' < $1) > $1._temp && mv $1._temp $1
```

Then, simply run `./crlftolf.sh myfile.txt` to convert `myfile.txt` to LF file endings. (Note, remember to run `chmod +x crlftolf.sh` to make the script executable).
