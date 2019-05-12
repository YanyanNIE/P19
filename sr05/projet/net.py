#!/Users/yanyan/anaconda3/bin/python
from sys import stdin, stderr, stdout
import select

import argparse

from codage import codage, decodage, codage_what, decodage_what

from common import *

from time import sleep

NAME = ''

verbose = False

def message_recu(message: str):
    """ Fonction appelée lorsqu'un message est reçu

        :param message: Message reçu
        :type message: str
    """
    what, who, where = decodage(message)
    variables = decodage_what(what)

    if who == where: return # Ce message est destiné au BAS du NET émetteur

    new_who = NAME

    if "appnet" in variables: # message reçu de NET
        if where == NAME: # nous est destiné, envoi à BAS
            del variables['appnet']
            log(verbose, NAME, "Message reçu de NET, envoi à BAS")
        else: # ne nous est pas destiné, retransmis à NET
            log(verbose, NAME, "Message reçu de NET, mais destiné à '{}'".format(where))
    else: # message reçu de BAS, envoi à NET
        variables['appnet'] = 'BAS'
        log(verbose, NAME, "Message de BAS, envoi à NET")

    new_what = codage_what(**variables)
    new_message = codage(new_what, new_who, where)
    log(verbose, NAME, "Envoi de: '{}'".format(new_message))
    stdout.write(new_message)
    stdout.flush()


if __name__ == "__main__":
    # Gestion des paramètres de commande
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--name', help='Name of node', required=True)
    args = parser.parse_args()

    NAME = args.name

    while(True):
        value = ""
        while stdin in select.select([stdin], [], [], 0)[0]:
            line = stdin.readline()
            if line:
                #value += line
                message_recu(line)
            sleep(1)
