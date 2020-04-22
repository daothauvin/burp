[![CircleCI](https://circleci.com/gh/daothauvin/burp.svg?style=shield&circle-token=f74b04aaa5d2902abc5866058190ef1484703670)](https://app.circleci.com/pipelines/github/daothauvin/burp?branch=master)
# BURP

> B.U.R.P - Basic Used for Robots Programming

## Auteurs

Par Dao Thauvin, Liece Cherchour et Thomas Bignon.

## Description

Le but de ce projet est d’implémenter en langage C un jeu de programmation dans le cadre du cours de CP6. Dans ce jeu, des robots s’entretuent dans une arène, chacun d’eux exécutant un script donné en début de partie. Le jeu se termine lorsqu’il ne reste plus qu’un seul robot encore fonctionnel dans l’arêne : son script est alors déclaré gagnant. Le langage de script que nous utiliserons est une version très simplifiée de l’antique langage BASIC. Le programme devra permettre la simulation de l’arène, ainsi que l’interprétation en temps réel du script de chaque robot.

## Sujet

Le projet est disponible [ici](docs/sujet_1.0.pdf).

### Script

- manipule entiers
- Commandes (extensible mais doit pouvoir être traduit dans language de base) :
	- Engine vitesse (en pourcentage), direction (angle)
    - Shoot direction `distance_explosion`

### Actions

- pause
- vitesse

### Launch

En premier temps, on peut utiliser les scripts `./build_main.sh` pour le programme principal
et `./build_test.sh` pour effectuer les tests

`./build_main.sh` se chargera de lancer le programme avec les fichiers prog[x].burp défini dans leur 
repertoire associé.

Par la suite, il suffit de faire :  `./burp prog1.burp ... prog4.burp` pour lancer le programme

#### Autre

- creation fichier forme data=value : https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html
