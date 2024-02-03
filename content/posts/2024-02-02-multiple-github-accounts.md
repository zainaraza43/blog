---
title: How to Use Multiple GitHub Accounts on One PC
date: 2024-02-02
draft: false
author: Jeremie Bornais
--- 

There are multiple ways to set up multiple GitHub accounts on one PC. For me, however, I prefer a solution that is more portable and requires less configuration. Thus, the solution I show here uses separate SSH keys for the two accounts, and the way you choose which account to use is by modifying the remote address of the GitHub repository. Only one small configuration file is required.

## Prerequesites

Before you can begin, you'll need to ensure you have Git and OpenSSH installed (Git typically comes with OpenSSH). You can download Git [here](https://git-scm.com/downloads).

After this, you'll need to ensure you have ssh-agent properly configured and started. For Windows users, use the following two commands in an admin powershell to set ssh-agent to automatically start (and then manually start it for this session):

```powershell
Get-Service ssh-agent | Set-Service -StartupType Automatic -PassThru | Start-Service
start-ssh-agent.cmd
```

## Creating the SSH Keys

Create SSH keys via the following command:

```sh
ssh-keygen -t ed25519
```

When prompted for a file to save it to, I recommend saving it to a file called `~/.ssh/id_<your_github_username>`, replacing `<your_github_username>` with your GitHub username. This is so it's easy to tell what this SSH key is for at a later date. Make sure to generate two keys, one for each of your two GitHub accounts.

## Adding the SSH Keys to GitHub

Head over to [github.com/settings/keys](https://github.com/settings/keys) and add your relevant **public key** to your account. You can get the contents of your public key by running:

```sh
cat ~/.ssh/id_<your_github_username>.pub
```

## Adding Your SSH Keys to SSH-Agent

Run the following command for each of your two SSH keys to add them to the SSH-Agent:

```sh
ssh-add ~/.ssh/id_<your_github_username>
```

## Creating the SSH Config

Create the file `~/.ssh/config` and put the following in it:

```
# github <account1>
Host <account1>.github.com
HostName github.com
PreferredAuthentication publickey
IdentityFile ~/.ssh/id_<account1>

# github <account2>
Host <account2>.github.com
HostName github.com
PreferredAuthentication publickey
IdentityFile ~/.ssh/id_<account2>
```

**NOTE:** Replace `<account1>` and `<account2>` with your two GitHub account usernames.

## Using Your Two Accounts

You're now all set to use your two accounts on your PC! Now, any time you want to clone a GitHub repository from a specific account, make sure to use SSH, and make sure you use the proper url.

Normally, the url will look something like this: `git@github.com:jere-mie/blog.git`. You just need to change the `github.com` to whatever you put for the `Host` in your SSH config. So, it'll look something like `git@account1.github.com:jere-mie/blog.git`.

Thus, to clone a repo at that address, you'd run:

```sh
git clone git@account1.github.com:jere-mie/blog.git
```

## Credits

Thanks for the two following resources which helped me through this process:

- [This video on using multiple GitHub accounts on your device](https://www.youtube.com/watch?v=jGwD3e1BZ5Y)
- [This article on SSH-Agent on Windows](https://interworks.com/blog/2021/09/15/setting-up-ssh-agent-in-windows-for-passwordless-git-authentication/)
