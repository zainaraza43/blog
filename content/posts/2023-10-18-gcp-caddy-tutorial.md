---
title: Using GCP's Free VPS to Host Unlimited Full-Stack Websites
date: 2023-10-18
draft: false
author: Jeremie Bornais
--- 

One of the most difficult steps of web development for beginners is the final step - actually getting your website online. There are hundreds of platforms out there that allow you to put your website online, and it can be difficult for a beginner to choose the right one for them.

As you continue in your web development journey, you'll most likely find a solution that fits and scales to your specific needs. However, most of us aren't building web applications that need to scale to thousands of concurrent users, and just need a way to get some hobby projects online.

This tutorial will guide you through the process of setting up your own Virtual Private Server (VPS). This is a (virtual) Linux machine that you'll have full control over and can use to host as many projects/websites as it can handle. From Discord bots to full stack web applications to public APIs to mail servers, you can pretty much put whatever you want on this server. This is the beauty of using a VPS to host your applications - you're given a machine and you can put whatever you want on it. The best part is this server is offered by GCP for free forever. There are no trials that end after 12 months - you simply sign up and get access to a free VPS, no strings attached. 

GCP offers a variety of other products for free, which I recommend you check out here: [cloud.google.com/free](https://cloud.google.com/free)

## Signing up for and Configuring GCP

- Head to the Google Cloud Platform Console [(console.cloud.google.com)](https://console.cloud.google.com/) and sign in with your Google account.
- Create a new project
- Enable billing and input your credit/debit card or other billing details
- Enable Compute Engine

**NOTE**: Although your credit/debit card is required, your VPS will remain free forever.

## Creating Your First VPS

- Head to `Compute Engine > VM Instances`
- Select `Create Instance`
- Name your instance whatever you want, and can keep the zone and region as whatever the default is (some regions aren't free, so stick with whatever the default is).
- Change the `Machine Type` to `e2-micro`
    - This is so that you can get the server for free!
- Under `boot disk` select `change`
- I recommend setting the version to `Debian 11` or, if you prefer Ubuntu, change `Operating System` to Ubuntu, and select whatever version you like
- Change the `boot disk type` to `Standard persistent disk`
    - You can change the size to up to 30GB for free. The default is 10GB.
- **IMPORTANT** - make sure to check the boxes saying `Allow HTTP traffic` and `Allow HTTPS traffic` under `Firewall`
  - If the boxes aren't checked, people cannot visit your website!
- Hit `Create`

Your VPS is now created! You can access it by hitting the `SSH` button in the VM Instances list.

## Reserving a Static IP Address

A static IP address needs to be reserved so that your server's IP address won't change, and you won't need to update DNS records periodically.

- Click the hamburger menu in the navbar and go to `VPC Network > IP Addresses`
- You should see your VPS' **External** IP address listed
- At the far right, click the three dots and select `Promote to static IP address`
- Choose a name for the IP address and select `Reserve`

Make sure to take note of this IP address for when you connect it to your domain!

**NOTE:** if you ever delete your VPS, make sure to also go back into `VPC Network > IP Addresses`, select the IP address, and click `Release Static Address`, otherwise you'll be charged for it. However, as long as you don't delete your VPS, you won't be charged for the IP address. 

## Connecting Your Domain to Your VPS

- Login to your domain provider (for example, Namecheap), and go to your DNS settings page
- Create a new A record for your domain:
  - Under `host` you may need to leave it blank or put `@` depending on your domain provider
    - This connects the `apex` domain to your VPS (for example, example.com).
    - If you prefer a subdomain, such as `www`, put that here instead (for example, www.example.com)
    - If you want both your apex domain and `www`, create two `A` records
  - Under `value` put the IP address from the above step

## Installing Necessary Software 

Run the following commands to install the necessary software to get your website running:

```bash
sudo apt update
# installing common and useful software, update this to your needs
sudo apt install python3 python3-pip build-essential git htop vim screen dnsutils neofetch wget tmux nano lsof
# minimal, quality-of-life-improving vim config. Feel free to substitute for your own
curl -fLo ~/.vimrc https://raw.githubusercontent.com/jere-mie/dotfiles/main/minimal.vim
```

**NOTE:** People with some experience with Linux and Debian-based systems may be tempted to run `sudo apt upgrade` here. While I do recommend doing this at some point, I'd recommend waiting until you're done with the rest of this setup process. This is because `google-cloud-sdk`, one of the packages installed on GCP VMs, takes a notoriously long time to update. Thus, wait to run this until you're at a point where you don't mind letting your VPS idle for potentially up to an hour.

### Installing Caddy

Caddy is the reverse proxy we'll use to connect your domain to your website. You can find the most up-to-date install instructions here: [https://caddyserver.com/docs/install](https://caddyserver.com/docs/install#debian-ubuntu-raspbian), or run the commands below, which are updated as of 2023/10/18:

```bash
sudo apt install -y debian-keyring debian-archive-keyring apt-transport-https
curl -1sLf 'https://dl.cloudsmith.io/public/caddy/stable/gpg.key' | sudo gpg --dearmor -o /usr/share/keyrings/caddy-stable-archive-keyring.gpg
curl -1sLf 'https://dl.cloudsmith.io/public/caddy/stable/debian.deb.txt' | sudo tee /etc/apt/sources.list.d/caddy-stable.list
sudo apt update
sudo apt install caddy
```

## Configuring Caddy

Caddy is what we'll be using as a reverse proxy. Essentially what that means is it will take requests to your domain (for example, when someone goes to www.example.com), and pass them to the actual process that is running your website (for example, a NextJS application or a Flask server).

We configure caddy using a file called `Caddyfile` (no file extension). Use the following commands to create a Caddyfile and start caddy.

```bash
cd ~
touch Caddyfile

# here, put in your Caddyfile config
nano Caddyfile

sudo caddy stop
sudo caddy start
```

Here is a sample Caddyfile for connecting the domain `example.com` and `www.example.com` to a web application running on port 8080.


```
www.example.com example.com {
    reverse_proxy localhost:8080
}
```

**NOTE:** Make sure to change the domain from `example.com` to your actual domain in your Caddyfile.

### Updating the Caddyfile

Any time you want to make changes to your Caddyfile (for example, changing the domain or adding another website), you'll need to make sure you're in the right directory when restarting caddy. Thus, make sure to keep your Caddyfile in a central location you'll remember. In this tutorial, we used the home directory, `~`.

Thus, to update your caddy configuration, run the following commands:

```bash
cd ~
# edit the file as necessary
nano Caddyfile
sudo caddy stop
sudo caddy start
```

## Setting up a Sample Site

If you already have a specific web application you'd like to host, you can use that here instead. However, to just get something running, here is a simple Python web server that just runs a "Hello World" website on port 8080. Save the following to a file, say, `website.py`:

```py
import http.server

PORT = 8080

class CustomHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        self.wfile.write(b'<h1>Hello World!</h1>')

httpd = http.server.ThreadingHTTPServer(('localhost', PORT), CustomHandler)

print(f'Serving on http://localhost:{PORT}')
httpd.serve_forever()
```

You can now run the application with the command:

```bash
python3 website.py &
```

Notice that we use `&`. This runs the application in the background. You'll need to be careful with running applications in the background like this because it can be difficult to find and stop them later if you're not familiar with Linux.

To terminate the process running on port 8080 (our sample website), we can use the following command:

```bash
kill -9 $(lsof -t -i:8080)
```

Alternatively, you can use something like `screen` instead of running the website in the background, or you can set it up as a systemd service, but that's outside the scope of this tutorial.

## Conclusion

You should now be able to go to your domain and see the sample website!
