# TD2 Machine sur une seule séance de 2h 

## ex1 - Prélèvement périodique de température
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

## ex2 - Synchronisation par signaux
un programme dans lequel un processus crée un processus fils. Les deux processus communiquent en utilisant le signal SIGUSR1. 

- Le fils affiche des lettres minuscules de « a » à « z ».
- Le père affiche les lettres majuscules de « A » à « Z ».

Ecrire le programme de telle sorte que le texte affiché sera comme suit :

```
aAbcBCdefDEFghijGHIJklmnoKLMNOpqrstuPQRSTUvwxyzVWXYZ 
```

**Indice** : installer un handler de `SIGUSR1` (en utilisant `sigaction`) au niveau du père et un autre handler au niveau du fils. Quand un processus affiche sa part de lettres, il réveille l'autre processus en lui envoyant un signal `kill(pid,SIGUSR1)`, puis il attend (`pause()`) qu'il soit réveillé par l'autre processus quand il aura terminé d'afficher sa part de lettres. 