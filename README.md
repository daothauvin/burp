[![CircleCI](https://circleci.com/gh/daothauvin/burp.svg?style=shield&circle-token=f74b04aaa5d2902abc5866058190ef1484703670)](https://app.circleci.com/pipelines/github/daothauvin/burp?branch=master)
# BURP

> B.U.R.P - Basic Used for Robots Programming

## Langage BURP et descriptif du sujet

La sémantique du langage BURP est disponible [ici](docs/grammar/diagram.xhtml) référencée dans le sujet disponible [ici](docs/sujet_1.0.pdf).

## Description

Le but de ce projet est d’implémenter en langage C un jeu de programmation dans le cadre du cours de CP6. Dans ce jeu, des robots s’entretuent dans une arène, chacun d’eux exécutant un script donné en début de partie. Le jeu se termine lorsqu’il ne reste plus qu’un seul robot encore fonctionnel dans l’arêne : son script est alors déclaré gagnant. Le langage de script que nous utiliserons est une version très simplifiée de l’antique langage BASIC. Le programme devra permettre la simulation de l’arène, ainsi que l’interprétation en temps réel du script de chaque robot.

## Dépendances

* CMake (>= 3.0) [cmake](https://cmake.org/)

* Check (>= 0.10.0) [check](https://libcheck.github.io/check/)

* PkgConfig (>= 0.29) [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/)

* Glib (>= 2.0) [glib](https://github.com/GNOME/glib)

* NCurses (>= 6.1) [ncurses](https://invisible-island.net/ncurses/ncurses.html)

* Subunit (>= 1.20) [subunit](https://packages.ubuntu.com/xenial/libsubunit-dev)


## Diagramme de classe

TODO

## Launch

En premier temps, on peut utiliser les scripts `./build_main.sh` pour le programme principal
et `./build_test.sh` pour effectuer les tests

`./build_main.sh` se chargera de lancer le programme avec les fichiers prog[x].burp défini dans leur 
repertoire associé.

Par la suite, il suffit d'utiliser l'exécutable se trouvant dans `build\src\` en faisant :  
`./burp prog1.burp ... prog4.burp` pour lancer le programme

### Contrôle de l'utilisateur : 

L'utilisateur dispose de 4 contrôles pour altérer l'interface utilisateur et le déroulement de la partie.

Pause : p  
Quitter : q  
Accélérer : +  
Décélérer : -  

## Auteurs

[Dao Thauvin](https://github.com/daothauvin)  
[Liece Cherchour](https://github.com/LieceC)  
[Thomas Bignon](https://github.com/totocptbgn)  
