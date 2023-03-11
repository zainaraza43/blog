#!/bin/sh
mkdir 2140-javacup
cd 2140-javacup
mkdir JLex
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
