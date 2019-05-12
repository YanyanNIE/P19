#!/Users/yanyan/anaconda3/bin/python

from sys import stdin, stderr, stdout
import select

from codage import codage, decodage, codage_what, decodage_what

from random import randint

import argparse
from common import *
from file import *

from time import sleep

verbose = True

NAME = ''
MAX = 0
PRIX = -1
FLAG = True

SNAPSHOT_PRIX = 0

def augEnchere():
    global PRIX

    pa = randint(3, 10)
    if PRIX + pa > MAX:
        PRIX = MAX
    else:
        PRIX = PRIX + pa

def message_envoie(file: str):
    global PRIX

    site = int(NAME)
    who = NAME
    chaine, where = defiler(file)

    variables = {"prix": PRIX, "file": chaine}

    what = codage_what(**variables)
    code = codage(what, who, where)
    stdout.write(code)
    stdout.flush()

def message_recu(message: str):
    global PRIX
    global SNAPSHOT_PRIX
    global FLAG

    file = ''
    what,who,where = decodage(message)
    variables = decodage_what(what)

    if "prix" in variables:
        PRIX = int(variables["prix"])

    # Ce message ne nous est pas destiné
    if "appnet" in variables:
        return

    if "file" in variables and len(variables["file"]) == 0:
        stderr.write("""\n
##################\n
Gagnant: {}\n
Prix de vente: {}\n
##################\n
        """.format(NAME, PRIX))
        return


    # message pour snapshot
    if "snapshot" in variables and variables["snapshot"] == "true":
        if FLAG:
            SNAPSHOT_PRIX = PRIX
            log(verbose, NAME, "Sauvegardé: '{}'".format(SNAPSHOT_PRIX))
            FLAG = False
            where = 1 if int(NAME) == 4 else int(NAME) +1

            if who == '': who = NAME
            what = codage_what(**{"snapshot": "true"})
            stdout.write(codage(what, who, where))
            stdout.flush()
    elif "synchro" in variables and variables['synchro'] == "true":
        PRIX = int(variables['prix'])
    elif PRIX < MAX and "prix" in variables and "file" in variables: # message pour le passage de droit
        FLAG = True
        augEnchere()
        file = enfiler(variables['file'], NAME)
        for i in range(1, 5): #1..4
            if str(i) != NAME:
                what = codage_what(**{"synchro": "true", "prix": PRIX})
                stdout.write(codage(what, NAME, str(i)))
                stdout.flush()

        sleep(1)
        message_envoie(file)
    elif PRIX >= MAX and "prix" in variables and "file" in variables:
        message_envoie(variables['file'])

if __name__ == "__main__":
    # Gestion des paramètres de commande
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--name', help='Name of node', required=True)
    args = parser.parse_args()
    NAME = args.name

    MAX = randint(60, 80)

    while(True):
        value = ""
        while stdin in select.select([stdin], [], [], 0)[0]:
            line = stdin.readline()
            if line:
                #value += line
                message_recu(line)
        sleep(1)
