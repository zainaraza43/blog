---
title: How to Enable Mouse Support in Tmux
date: 2022-06-13
draft: false
---

While I wouldn't necessarily recommend using the mouse too often when using Tmux, it's likely that you may want it to be enabled at some point, so it may be better to enable it before you need it.

The process is simple, you simply need a config file `.tmux.conf` in your home directory which contains the text `set -g mouse on`.

You can do this automatically with the following command:
```sh
echo "set -g mouse on" > ~/.tmux.conf
```

Congratulations! You now have mouse support enabled in tmux. You can now use the mouse to move between and resize windows.

Interested in *not* using the mouse? Check out the man page for tmux [here](https://manpages.ubuntu.com/manpages/bionic/man1/tmux.1.html#:~:text=command%20is%20assumed.-,KEY%20BINDINGS,in%20the%20current%20window%20forwards.) (or type `man tmux` in your terminal).