CORBATÜR
========

Lancer corbatur
---------------
Après avoir compilé le programme, lancez-le à l'aide du script ```corbatur``` :

```bash
$ ./corbatur <pseudo> [port]
```
Si vous avez à votre disposition le programme ```rlwrap```, il est vivement
recommandé de l'utiliser :

```bash
$ rlwrap -a ./corbatur <pseudo> [port]
```

Compiler
--------

Il vous faut de quoi compiler le C++ et les bibliothèques de développement
de python.

```bash
$ make omniorb
$ make
```

License
-------
Copyright © 2014 Harenome RAZANAJATO, Jérémy MEYER

Ce projet est libre. Vous pouvez le redistribuer ou le modifier selon les termes
de la license « Do What The Fuck You Want To Public License », Version 2, comme
publiée par Sam Hocevar. Pour de plus amples informations, veuillez vous référer
au fichier COPYING, ou bien http://www.wtfpl.net/.
