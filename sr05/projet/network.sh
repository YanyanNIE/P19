#!/bin/bash

killall net.py 2> /dev/null
killall bas.py 2> /dev/null
killall cat 2> /dev/null
killall tee 2> /dev/null

rm /tmp/in* 2> /dev/null
rm /tmp/out* 2> /dev/null

# Création des fifos
mkfifo /tmp/inN1 /tmp/outN1
mkfifo /tmp/inB1 /tmp/outB1

mkfifo /tmp/inN2 /tmp/outN2
mkfifo /tmp/inB2 /tmp/outB2

mkfifo /tmp/inN3 /tmp/outN3
mkfifo /tmp/inB3 /tmp/outB3

mkfifo /tmp/inN4 /tmp/outN4
mkfifo /tmp/inB4 /tmp/outB4

# Lancement des sites
./net.py --name 1 > /tmp/outN1 < /tmp/inN1 &
./bas.py --name 1 > /tmp/outB1 < /tmp/inB1 &

./net.py --name 2 > /tmp/outN2 < /tmp/inN2 &
./bas.py --name 2 > /tmp/outB2 < /tmp/inB2 &

./net.py --name 3 > /tmp/outN3 < /tmp/inN3 &
./bas.py --name 3 > /tmp/outB3 < /tmp/inB3 &

./net.py --name 4 > /tmp/outN4 < /tmp/inN4 &
./bas.py --name 4 > /tmp/outB4 < /tmp/inB4 &

#Sortie de chaque BAS dans l'entrée de son NET
cat /tmp/outB1 > /tmp/inN1 &
cat /tmp/outB2 > /tmp/inN2 &
cat /tmp/outB3 > /tmp/inN3 &
cat /tmp/outB4 > /tmp/inN4 &

# Sortie de chaque NET dans l'entrée de son BAS et dans l'entrée du prochain NET
cat /tmp/outN1 | tee /tmp/inB1  /tmp/inN2 &
cat /tmp/outN2 | tee /tmp/inB2  /tmp/inN3 &
cat /tmp/outN3 | tee /tmp/inB3  /tmp/inN4 &
cat /tmp/outN4 | tee /tmp/inB4  /tmp/inN1 &
