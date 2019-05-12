## Projet

#### Objectifs

Les objectifs de cette réalisation sont les suivants :

Concevoir une application répartie sur la base des algorithmes déjà vus en cours.
Programmer une application répartie et se rendre compte des problèmes à surmonter.
Prendre en main une suite logicielle issue de la recherche pour les réseaux dynamiques.
Travailler en groupe, s'organiser et savoir gérer d'éventuelles tensions.
Progresser en autonomie, rendre compte de son travail en fin de période par une soutenance orale en groupe.


#### Sujet
Le sujet du projet consiste à programmer une application répartie utilisant des données partagées (il inclut aussi l'étape 2 de prise en main des outils décrite ci-dessus) :

- Réaliser le scénario :
    - Définir un scénario d'application répartie qui nécessite le partage d'au moins une donnée : plusieurs instances de l'application réparties dans un réseau travaillent sur des réplicats.
    - Définir l'architecture de l'application afin de séparer l'utilisation des données et leur gestion : les mécanismes répartis de synchronisation des réplicats et de sauvegardes sont sous-traités à une application de contrôle. S'inspirer des applications BAS et NET du tutoriel. Plus de deux applications par site pourraient être utilisées si besoin.
    - Constituer un ou plusieurs réseaux utilisant le shell en vous inspirant du tutoriel Airplug. Il est possible d'utiliser plusieurs machines avec nc (cf. cette page de la documentation).

- Pour garantir la cohérence des réplicats, une solution d'exclusion mutuelle répartie est utilisée.
    - Utiliser l'algorithme de la file d'attente répartie décrit en amphi et donné ci-dessous.
    - La section critique correspond à l'accès exclusif à la donnée. A vous de voir s'il faut une exclusion mutuelle pour l'écriture et la lecture de la donnée partagée. A vous de voir comment adapter l'algorithme pour diffuser la mise à jour de la donnée partagée.
- Pour garantir la sauvegarde répartie du système, un algorithme de calcul d'instantané (snapshot) est utilisé.
    - On choisira l'un des algorithmes vus en cours (chapitre 6).
    - Pour s'assurer de la cohérence de la sauvegarde répartie, on utilisera des horloges vectorielles (chapitre 5) afin de dater les sauvegardes locales et de vérifier a posteriori qu'elles définissent une coupure cohérente.