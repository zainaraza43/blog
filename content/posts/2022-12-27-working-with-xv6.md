---
title: Getting Started and Working With XV6
date: 2022-12-27
draft: false
---

## Introduction

XV6 is a re-implementation of the Unix operating system that was developed as a teaching tool for MIT's operating systems course. It is based on the original Unix operating system, which was developed in the 1970s at Bell Labs. XV6 is written in C and runs on x86-based computers.

In the upcoming semester, I will be taking the Operating Systems course COMP-3300 at the University of Windsor, where we'll be working with XV6. This article serves as a place for me to write about how to work with XV6 from the point of view of someone who is just starting to play around with it. This is sometimes useful to people who are also trying something new for the first time, since more experienced people may gloss over small hurdles that newbies face.

In this article, I'm going to go over a few different things, namely:

- How to install XV6
- How to create a new command
- How to exit XV6 (this is going to be a short one, but oddly enough a lot of tutorials leave out this detail, which is annoying to people just starting out like me)

This list will probably grow throughout my time taking the course, depending on whether I decide to create separate articles for different topics.

## How to Install XV6

Firstly, if you're a Windows user, you're going to need to use WSL. If you're not familiar with WSL, it essentially gives you a linux terminal on your Windows device. You can install WSL by simply typing `wsl --install` in an **admin Powershell** window. You can read more on installing WSL [here](https://learn.microsoft.com/en-us/windows/wsl/install).

For the purposes of this article, I'll be assuming you're using a Debian-based OS (like Ubuntu, Mint, or vanilla Debian). Ubuntu is the default installed by WSL.

Now, open up a Linux shell and type the following commands:

```sh
sudo apt update
sudo apt upgrade
sudo apt install git build-essential qemu-system
```

This should install all of the prerequesite software to get XV6 up and running. Now all you need to do is download XV6 and run it:

```sh
git clone https://github.com/mit-pdos/xv6-public
cd xv6-public
make qemu-nox
```

Congratulations! You've now installed and run XV6. You can play around and try out the different commands. When you want to exit XV6, just type `ctrl-a x` in the terminal and you should be brought back to your original shell.

Pro tip: run `make clean` to clean up and remove all of the compiled files if you're actively working on something. It will make the directory a little cleaner and easier to find what you're looking for.

## How to Create a New Command

For the purposes of this section I'm not going to create a completely new command, we'll just be copying one of the existing commands, `rm` into a new command `rm2`. The process will be the exact same though when you want to write a command that does something different.

Now, firstly you'll need to create a new command, which we'll do by copying `rm`:

```sh
cp rm.c rm2.c
```

Now, we need to edit the `Makefile` to include the new command. You can use your editor of choice. I use vim, but if you're not familiar with vim then nano might be a good option:

```sh
nano Makefile
```

Now, you'll need to make adjustments in two places to make your new command executable.

You should see a section like this on around line 168:

```makefile
UPROGS=\
        _cat\
        _echo\
        _forktest\
        _grep\
        _init\
        _kill\
        _ln\
        _ls\
        _mkdir\
        _rm\
        _sh\
        _stressfs\
        _usertests\
        _wc\
        _zombie\
```

Simply add `_rm2\` to the end, to make it:

```makefile
UPROGS=\
        _cat\
        _echo\
        _forktest\
        _grep\
        _init\
        _kill\
        _ln\
        _ls\
        _mkdir\
        _rm\
        _sh\
        _stressfs\
        _usertests\
        _wc\
        _zombie\
        _rm2\
```

Now, at roughly line 251 you should see something like this:

```makefile
EXTRA=\
        mkfs.c ulib.c user.h cat.c echo.c forktest.c grep.c kill.c\
        ln.c ls.c mkdir.c rm.c stressfs.c usertests.c wc.c zombie.c\
```

Simply add `rm2.c` after `zombie.c` to make it:

```makefile
EXTRA=\
        mkfs.c ulib.c user.h cat.c echo.c forktest.c grep.c kill.c\
        ln.c ls.c mkdir.c rm.c stressfs.c usertests.c wc.c zombie.c rm2.c\
```

You can now save and close the Makefile, and the next time you run XV6, you should be able to use the `rm2` command in the same way as the `rm` command!

## How to Exit XV6

Like I mentioned in the introduction, this is a very simple thing to do but if often left out of tutorials for some reason. It's as easy as typing `ctrl-a x` in the terminal 😎.
