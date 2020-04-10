[![CircleCI](https://circleci.com/gh/daothauvin/BURP.svg?style=svg&circle-token=f74b04aaa5d2902abc5866058190ef1484703670)](https://app.circleci.com/pipelines/github/daothauvin/burp?branch=master)
# BURP

> B.U.R.P - Basic Used for Robots Programming

## Auteurs

Par Dao Thauvin, Liece Cherchour et Thomas Bignon.

## Description

Le but de ce projet est d’implémenter en langage C un jeu de programmation dans le cadre du cours de CP6. Dans ce jeu, des robots s’entretuent dans une arène, chacun d’eux exécutant un script donné en début de partie. Le jeu se termine lorsqu’il ne reste plus qu’un seul robot encore fonctionnel dans l’arêne : son script est alors déclaré gagnant. Le langage de script que nous utiliserons est une version très simplifiée de l’antique langage BASIC. Le programme devra permettre la simulation de l’arène, ainsi que l’interprétation en temps réel du script de chaque robot.

## Sujet

Le projet est disponible [ici](docs/sujet_1.0.pdf).

## Notes

### `#define`

- taille de l’arène -> 10 000 × 10 000
- vitesse maximum -> 10 (unités par cycle -> bouge de 10 cases)
- vitesse missile -> 500 (unités)
- distance maximale d’explosion -> 7000 (unités)
- taille du robot -> 10 × 10
- nombre de missile max par robot -> 2
- low_range -> 50 unités
- degat_explosion_low_range -> 10%
- mid_range -> 200 unités
- degat_explosion_mid_range -> 5%
- high_range -> 400 unités
- degat_explosion_high_range -> 3%
- temps_loop -> ?

### Départ

- positions robots -> coins de l'arène
- nombre de robots -> 4

### Implémentation

- coordonnées -> double
- position du robot -> centré dans un carré
- collision = arrêt

### Script

- manipule entiers
- Commandes (extensible mais doit pouvoir être traduit dans language de base) :
	- Engine vitesse (en pourcentage), direction (angle)
    - Shoot direction `distance_explosion`

### Actions

- pause
- vitesse

### Launch

	./burp prog1.burp ... prog4.burp

### Roles

- affichage [ ncurses, Actions, Launch ]
- gestion cycles [ mise à jour, collisions, Depart, Implementation ]
- interpreteur [ Script, [traducteur] ]

### GLib

GLib doc : https://developer.gnome.org/glib/stable/

#### General

- structures : https://developer.ibm.com/tutorials/l-glib/ (liste,arbre, file, table de hachage)
- memoire : https://developer.gnome.org/glib/stable/glib-Memory-Allocation.html
- gestion string : https://developer.gnome.org/glib/stable/glib-String-Utility-Functions.html
- gestion random : https://developer.gnome.org/glib/stable/glib-RandomNumbers.html
- utiliser des commandes shell : https://developer.gnome.org/glib/stable/glib-Shell-related-Utilities.html

#### Utile pour affichage

- timer : https://developer.gnome.org/glib/stable/glib-Timers.html

#### Utile pour commande

- gestion options commande : https://developer.gnome.org/glib/stable/glib-Commandline-option-parser.html

#### Utile pour interpréteur

- syntaxe expressions régulières : https://developer.gnome.org/glib/stable/glib-regex-syntax.html

- gestion regex : https://developer.gnome.org/glib/stable/glib-Perl-compatible-regular-expressions.html | https://developer.gnome.org/glib/stable/glib-Glob-style-pattern-matching.html

**Remarque** : le premier lien est plus complet

- gestion file : https://developer.gnome.org/glib/stable/glib-File-Utilities.html

- Scanner : https://developer.gnome.org/glib/stable/glib-Lexical-Scanner.html#g-scanner-input-file

#### Autre

- creation fichier forme data=value : https://developer.gnome.org/glib/stable/glib-Key-value-file-parser.html

# Exterior Needs
## Modele
### Parser

### Game Management

## Vue
acces to missile/robot (**Do not impact robots**)
update() -> mise a jour de la vue

## Controlleur
