---
title: Turning My 8 Year Old Chromebook Into a Home Server 
date: 2024-01-18
draft: false
author: Jeremie Bornais
--- 

*This article purposely doesn't go into specifics or provide a step-by-step tutorial. I'll be writing a separate article on this later.*

Roughly 6 years ago I was in the market for a small and simple laptop to use when traveling and for school. At the time I had a gaming laptop (a purchase I still regret) which worked well for any gaming or heavy computing tasks I needed to perform. However, it was heavy, bulky, and would only last an hour or so on battery. After doing some research, I figured a cheap, refurbished Chromebook would work well for my needs (at least until I decided to purchase a new Windows device). So, I went on Ebay and got a $100 refurbished Chromebook.

Over the next couple of years, the Chromebook served me quite well. I eventually upgraded the storage to 128gb (from 16gb) and played around with Crostini (Google's official way of running Linux apps on Chromebooks). At this point, I purchased a new Windows laptop, and I could confidently say I got my $100 worth of value out of this Chromebook. For the next few years, I'd occasionally boot it back up for one reason or another. However, for all intents and purposes, this Chromebook just sat on a shelf collecting dust.

Fast forward to a few weeks ago - I saw [this video](https://www.youtube.com/watch?v=IuRWqzfX1ik) on YouTube about making your own home server from an old laptop, and I was inspired. I spent the next little while researching how I could do this on my Chromebook, and discovered [MyChromeBox](https://mrchromebox.tech/). Using his guide on updating the Chromebook's firmware, I was able to flash a new BIOS on it and boot Ubuntu Server from a USB drive.

From there, the process was pretty much the same as any other home server. I installed the software I needed, set up DNS records on my domain to point to my home server, and set up port forwarding on my router to open my server to the public.

I'm still learning more about home servers and self hosting, and I welcome advice or ideas on how I can improve my setup. However, I thought this article would be useful to anyone who has a Chromebook (or any old laptop, really) lying around and collecting dust.

I know that there's a big problem right now with schools needing to get rid of old Chromebooks, with many of them becoming e-waste. Perhaps this is a good option for those Chromebooks that would otherwise be thrown away.
