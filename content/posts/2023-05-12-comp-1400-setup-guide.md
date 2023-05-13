---
title: COMP-1400 Dev Environment Setup Guide
date: 2023-05-12
draft: true
author: Jeremie Bornais (with help from ChatGPT 😎)
---

Setting up a development environment on Windows for coding in C can seem daunting for a new CS student. However, with the right tools and a step-by-step guide, the process can be straightforward. In this tutorial, we will walk through the process of setting up a development environment on Windows for coding in C.

## Step 1: Install WSL

WSL (Windows Subsystem for Linux) is a compatibility layer that allows running Linux binaries natively on Windows. It provides an easy way to get a full Linux environment running on Windows, including a terminal and package manager.

To install WSL, follow these steps:

1. Open the Microsoft Store app on your Windows machine.
1. Search for "WSL" in the search bar and select "Ubuntu" from the list of available options.
1. Click on the "Get" button to start the installation process.
1. Once the installation is complete, launch Ubuntu from the Start menu to start using WSL.

## Step 2: Install GCC

GCC (GNU Compiler Collection) is a collection of programming language compilers, including C. It is an essential tool for compiling and running C programs.

To install GCC on Ubuntu, follow these steps:

1. Open a terminal window in Ubuntu by typing "ubuntu" in the Start menu search bar and selecting "Ubuntu" from the list of results.
1. Run the following command to update the package list: sudo apt-get update
1. Run the following command to install GCC: sudo apt-get install build-essential

## Step 3: Install VSCode

Visual Studio Code (VSCode) is a popular code editor with many features, including syntax highlighting, debugging, and extensions. It is a powerful tool for writing and editing C programs.

To install VSCode on Windows, follow these steps:

1. Go to the VSCode website at https://code.visualstudio.com/.
1. Click on the "Download for Windows" button to download the installer.
1. Run the installer and follow the on-screen instructions to complete the installation process.

## Step 4: Configure VSCode

Once you have installed VSCode, you need to configure it to work with WSL and GCC. Follow these steps to set up the necessary configurations:

1. Open VSCode on Windows.
1. Install the "Remote - WSL" extension by clicking on the "Extensions" icon in the left-hand toolbar and searching for "Remote - WSL."
1. Click on the "Remote Explorer" icon in the left-hand toolbar.
1. Click on the "Connect to a Remote Host" button and select "Remote-WSL: New Window" from the dropdown menu.
1. In the new VSCode window that opens, click on the "Terminal" tab and select "New Terminal" from the dropdown menu.
1. In the terminal, run the following command to test that GCC is installed and working correctly: gcc --version
1. Create a new C file in VSCode by clicking on the "File" menu and selecting "New File." Save the file with a .c extension.
1. Write your C code in the new file and save it.
1. Compile your code by opening a terminal in VSCode and running the following command: gcc filename.c -o filename
1. Run your program by opening a terminal in VSCode and running the following command: ./filename

Congratulations! You have now set up a development environment on Windows for coding in C. You can use this environment to write, compile, and run C programs.

## Appendix

### Sample C Program

Here is a sample "hello world" C program you can use to test your new dev environment:

```c
#include <stdio.h>

int main(){
    printf("Hello World!\n");
}
```
