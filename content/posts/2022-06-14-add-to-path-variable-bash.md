---
title: How to Add a Directory to the PATH Variable in Bash
date: 2022-06-14
draft: false
---

If you ever wanted to install something from source, or create handy scripts to use anywhere in bash, you'll need to update the PATH variable. Simply put, the PATH variable is a string consisting of colon-separated (:) directories. Whenever you type a command into the terminal, all of these directories are checked for executables that match the command you typed.

Now, let's say we have a directory we created, `~/.bin/` which contains our homemade scripts/executables. To add this to PATH, we just need to update our `.bashrc` file. Edit this file with nano `nano ~/.bashrc` (or vim if you're cool 😎). Now, just add to the end of the file the following:

```sh
export PATH="$PATH:~/.bin"
```

After that, either exit out and re-open bash or type `source ~/.bashrc` to update bash. (You only need to do this once).

Congratulations! You have now updated your PATH variable. Now, any executable you put in `~/.bin` will be runnable from the terminal by default.
