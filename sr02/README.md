
## ex1
Nous désirons développer un programme qui permet de faire un prélèvement de température chaque 5
secondes. Entre deux mesures, le processus est occupé à faire autre chose (par exemple afficher une
barre de progression (---------). 

Pour ce faire, on utilisera une horloge qui émet un signal `SIGALRM` après un délai spécifié avec la fonction `alarm (....)` ; 

On considère que le thermomètre est un processus fils créé avec `fork()`. Ce thermomètre reste endormi dans une boucle (`pause ()`), et pour mesurer la température il faudra le réveiller avec le signal `SIGUSR1`. 

Quand le thermomètre reçoit le signal SIGUSR1, il se réveille et pour simuler la mesure de température, ce dernier tire un nombre aléatoire, compris entre 10 et 40, avec la fonction `random()`, et l'affiche en tant que température.

```
Programmez ce prélèvement périodique de température, 
en redéfinissant les handlers des signaux SIGUSR1 
(pour le processus thermomètre) et SIGALRM (pour le processus père). 
```

programme réalisé:

![](imgs/ex1.gif)

## ex2
un programme dans lequel un processus crée un processus fils. Les deux processus communiquent en utilisant le signal SIGUSR1. 

- Le fils affiche des lettres minuscules de « a » à « z ».
- Le père affiche les lettres majuscules de « A » à « Z ».

Ecrire le programme de telle sorte que le texte affiché sera comme suit :

```
aAbcBCdefDEFghijGHIJklmnoKLMNOpqrstuPQRSTUvwxyzVWXYZ 
```

## ex3 (Segment de mémoire partagée : Synchronisation père-fils)

fichers concernants: `sharemem.h`; `surv.c`; `f1.dat`; `f2.dat`; `survshm.c`


Vous allez avoir à inclure dans chacun de vos programmes plusieurs fichiers ".h". Il est plus simple,
pour ne pas en oublier, de créer un fichier "sharemem.h" qui contient :

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

Vos définitions globales puis de faire un unique #include "sharemem.h" au début de vos programmes. 

- Ecrire une fonction copiefichier(int f1, int f2) qui copie le contenu d’un fichier représenté par f1
dans un autre fichier représenté par f2. La fonction doit retourner le nombre d’octets copiés. La
taille maximale d’un bloc qu’on peut lire/écrire est de 1024 octets (#define MAXSIZE 1024).

- Ecrire un programme `surv.c` qui prend en argument deux fichiers (f1.dat et f2.dat) et surveille leurs
descripteurs de fichier en utilisant un parent et un fils : chaque processus affiche le contenu d’un
seul fichier à la sortie standard et écrit ensuite à la sortie standard le nombre total d'octets reçus. Ce
programme utilise la fonction copiefichier(int f1, int f2).

Voici un exemple d’exécution où `f1.dat` contient bonjour et `f2.dat` contient sr02 :
 
```
  $ ./ex f1.dat f2.dat
 bonjoursr02 Octes lus: 7
 Octes lus: 4
```

- Modifiez dans un programme `survshm.c` le programme surv.c pour que le parent et le fils partagent
un segment mémoire de petite taille. Le fils stocke son nombre d'octets (les octets lus à partir d’un
fichier) dans le segment de mémoire partagée. Le parent attend que le fis termine et affiche ensuite
le nombre d'octets reçus par chaque processus et la somme de ces valeurs. Le parent crée le segment
de mémoire partagée en utilisant la clé IPC_PRIVATE. La synchronisation de la mémoire partagée
est assurée par la fonction wait. Le parent n'accède pas à la mémoire partagée tant qu'il n'a pas
détecté la terminaison de son fils.

Voici un exemple d’exécution où f1.dat contient bonjour et f2.dat contient sr02 :

```
 $ ./ex2 f1.dat f2.dat
 bonjoursr02 Octes copies: 7 par le parent 4 par le fils
 11 au total 
```