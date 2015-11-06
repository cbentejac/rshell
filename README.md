# rshell
Written by Candice Bentéjac for the University of California - Riverside CS100 class (Fall 2015).

## Quick description of rshell
The program consists in a shell called *_rshell_*. This shell must be able to perform the following steps:
- Print a command prompt (like $).

In order to distinguish the normal shell from the *_rshell_*, € will be used instead of $ as a command prompt. 
*_rshell_* also displays the username and the host name.

- Read in a command (which has the form `cmd = executable [ argumentList ] [ connector cmd ]`) on one line.

"&&", "||" and ";" are the three connectors that can be used to link commands between each other on the same command line.


# Bugs à résoudre
- Problème d'exécution des commandes sans arguments telles que ls ou ps. Vient sous doute du fait que la liste d'argument est initialisée par défaut à "". 

	=> Avant de remplir char\* args[], vérifier si la liste d'argument est vide, et si tel est le cas, args[2] plutôt que args[3].
	RESOLU !!!
- Problème avec les connnecteurs && et || (ne pas oublier ; qui ne devrait pas fonctionner s'il colle l'exécutable de la commande suivante) lorsqu'ils sont collés à la liste d'arguments qu'ils suivent ou l'exécutable qu'ils précèdent.

	=> DEVRAIT SE FAIRE AU MOMENT DE SEPARATE() !!! Dans Parse.cpp (en local), toutes les fonctions (ou presque) permettant de traiter ces cas ont été écrites, il suffit donc de les copier/coller et de les réutiliser. Si le temps, écrire une fonction qui regroupe toutes ces fonctions ou qui d'office vérifie tous ces cas sans faire appel à trop de fonctions annexes (dans l'idéal).

# A faire (si le temps)
- Gérer le cas du cd.
- Vérifier nommages des variables et des méthodes (conventions (se baser sur celle de Java, puisque seule référence en POO), CalTech et "transparence").
- Raccourcir le code de certaines fonctions (mais probablement pas faisable dans les délais) ; certaines fonctions sont très longues en raison des {} pas toujours nécessaires (notamment dans les if/else) et surtout pas harmonisés (shame on me!).
- Aérer le code et commenter les CPP de façon pertinente.

# A finir 
- Tests
- Commentaires dans les HPP : suivre le format précédemment utilisé. La doc pourra être générée avec Doxygen (penser à vérifier avant l'envoi final, au cas où), le préciser dans le README.md.
- Makefile (voir création d'une arborescence interne à src car beaucoup de fichiers)
- Rédaction du README.md (in English please).

# Author
Candice Bentéjac

Université de Bordeaux / University of California, Riverside
