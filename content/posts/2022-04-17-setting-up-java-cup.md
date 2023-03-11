---
title: Instructions to Install Java Cup on Linux
date: 2022-04-17
draft: false
---

Just want all the commands? Check them out [here](#all-commands-in-one-block)  
Or, run this one command to do everything:

```bash
curl -o- https://blog.bornais.ca/assets/scripts/javacup-install.sh | bash
```

## Prerequesite Software

These instructions are for Linux machines. If you're a Windows user, I recommend using the [Windows Subsystem for Linux (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install). The only prerequesite software required is Java. If you're on a Debian-based system and don't have Java installed, you can install it via `sudo apt install default-jre` and `sudo apt install default-jdk`.

## Detailed instructions

### Make the 2140-javacup directory and cd into it

```bash
mkdir -p 2140-javacup
cd 2140-javacup
```

### Install JLex

```bash
mkdir -p JLex
cd JLex
curl https://blog.bornais.ca/assets/2140/lex/Main.java -o Main.java
javac Main.java
cd ..
```

### Install JavaCup

```bash
curl https://blog.bornais.ca/assets/2140/cup/javaCup.tar -o javaCup.tar
tar -xvf *.tar
rm *.tar
```

### Download all of the calc files

```bash
curl https://blog.bornais.ca/assets/2140/cup/calc.lex -o calc.lex
curl https://blog.bornais.ca/assets/2140/cup/calc.cup -o calc.cup
curl https://blog.bornais.ca/assets/2140/cup/CalcParserUser.java -o CalcParserUser.java
curl https://blog.bornais.ca/assets/2140/cup/calc.input -o calc.input
```

### Run it

```bash
java JLex.Main calc.lex
java java_cup.Main -parser CalcParser -symbols CalcSymbol calc.cup
javac calc.lex.java
javac CalcParser.java CalcSymbol.java CalcParserUser.java
java CalcParserUser
```

### Addendum

You may want to run the following once you're done just to clean up your directory:

```bash
rm *.class
```

Also, you may want to save the commands in [the "run it" section](#run-it) to a script file, such as `calc.sh`.
I've uploaded one for your convenience. You can download it by running:

```bash
curl https://blog.bornais.ca/assets/scripts/calc.sh -o calc.sh
```

And you can run it by running:

```bash
chmod +x calc.sh # you only need to do this once
./calc.sh
```

## All commands in one block

Below are all of the commands listed together. You can type them in one at a time, or run this one script:

```bash
curl -o- https://blog.bornais.ca/assets/scripts/javacup-install.sh | bash
```

Commands one at a time:

```bash
mkdir -p 2140-javacup
cd 2140-javacup

mkdir -p JLex
cd JLex

curl https://blog.bornais.ca/assets/2140/lex/Main.java -o Main.java
javac Main.java
cd ..

curl https://blog.bornais.ca/assets/2140/cup/javaCup.tar -o javaCup.tar
tar -xvf *.tar
rm *.tar

curl https://blog.bornais.ca/assets/2140/cup/calc.lex -o calc.lex
curl https://blog.bornais.ca/assets/2140/cup/calc.cup -o calc.cup
curl https://blog.bornais.ca/assets/2140/cup/CalcParserUser.java -o CalcParserUser.java
curl https://blog.bornais.ca/assets/2140/cup/calc.input -o calc.input

java JLex.Main calc.lex
java java_cup.Main -parser CalcParser -symbols CalcSymbol calc.cup
javac calc.lex.java
javac CalcParser.java CalcSymbol.java CalcParserUser.java
java CalcParserUser
```
