---
title: How to Disable the Bell in Windows Terminal
date: 2022-08-14
draft: false
---

If you're someone who uses Windows Terminal (and if you're not, you should be), you've probably encountered an annoying bell sound at one point or another. Whether it's from hitting backspace too many times, or pressing tab when you shouldn't have, this bell sound shows itself just often enough for it to be worth going through the steps to remove it.

Luckily, it's a very straightforward process to disable the sound. Simply go to the settings in Windows Terminal, then select the cog at the bottom to open your settings.json file. You'll probably see something like this:

```json
    ...
    "profiles": 
    {
        "defaults": {},
    }
    ...
```

What you want to do is locate the `"defaults":{}` portion. Note: there may already be some configuation options in the default profile. In this case, make sure you're just adding another property instead of removing them. What you now need to do is add one line in the "defaults" section to make it look like the following:

```json
    ...
    "profiles": 
    {
        "defaults":
        {
            "bellStyle": "none"
        },
    }
    ...
```

Congratulations! You now no longer have to listen to that annoying bell 😎
