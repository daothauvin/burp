[![CircleCI](https://circleci.com/gh/daothauvin/burp.svg?style=shield&circle-token=f74b04aaa5d2902abc5866058190ef1484703670)](https://app.circleci.com/pipelines/github/daothauvin/burp?branch=master)
# BURP

> B.U.R.P - Basic Used for Robots Programming

## Langage BURP et descriptif du sujet

La sémantique du langage BURP est disponible [ici](https://daothauvin.github.io/burp/html/grammar/diagram.xhtml) référencée dans le sujet disponible [ici](https://daothauvin.github.io/burp/html/sujet_1.0.pdf).

Le rapport du projet est disponible [ici](rendu/REPORT_CP6.pdf)

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


Diagramme de classe avec tout les fichiers :  
![Class_Diagram](https://daothauvin.github.io/burp/html/main_8c__incl.png)  
Pour plus de détail sur les différents fichiers : [page doxygen](https://daothauvin.github.io/burp/html/main_8c.html)  
Diagramme de classe avec les différents modules :  
![Diagram](https://daothauvin.github.io/burp/html/dir_68267d1309a1af8e8297ef4c3efbcdba_dep.png)   
Pour avoir plus d'informations : [page doxygen](https://daothauvin.github.io/burp/html/dir_68267d1309a1af8e8297ef4c3efbcdba.html)  
Model est séparé en deux sous modules :  
![Model_Diagram](https://daothauvin.github.io/burp/html/dir_5dd65160827af56e6353642206b80129_dep.png)  
Pour avoir plus d'informations : [page doxygen](https://daothauvin.github.io/burp/html/dir_5dd65160827af56e6353642206b80129.html)  

Lien vers la page doxygen du projet : [doxygen](https://daothauvin.github.io/burp/html/)

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
