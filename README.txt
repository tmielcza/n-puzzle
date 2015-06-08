Tom tu es horrible, je suis decue de travailler avec toi, je sais pas comment je vais faire pour tenir, tu dessines des bites et regardes des meufs a poil
Tu comprends rien. Tu mens. J'avoue. C'est vrai ? Tkt.
Ferme ta gueule, Tom.
<3 C'est ma bite

V 0) Calculer solution finale de la map
V 1) Faire A*
  - // classe Grille qui represente l'etat de la grille (1 pere, 2 fils au min, 4 au max)
  - // openlist = priority queue && closed list = map
  - // Verifier si ca fonctionne...
V 2) // Faire Manhattan
  V (+ 2/3 autres heuristiques) [LinearConflict OK, MisplacedTiles OK, Distance euclidienne]
V 3) Faire le parser
V 4) Calculer les stats
V 4 bis) gerer args (-s, taille, -b bidirectionnel, -h heuristique)
X 4 ter) Refaire ce Makefile pourri qui pue des fesseuis.olio
V 4 truc) Refaire les classes en coplien
V 5) Bidirectionnel (bonus)
~ 6) Faire une interface graphique (bonus)



ERROR

./npuzzle -s 2
./npuzzle -foror
./npuzzle -h false // SEGFAULT => regle
./npuzzle -b -h manhattan -s 5 map.txt kikoo
./npuzzle -s 18
./npuzzle -s
./npuzzle -h
./npuzzle -s -h
./npuzzle -b -b
./npuzzle map.txt basic_map.txt
./npuzzle noexist
./npuzzle basic_map.txt -h manhattan -s 4


OK
./npuzzle -s 4
./npuzzle -s 17
./npuzzle basic_map.txt -h manhattan
./npuzzle basic_map.txt -h linearconflict
./npuzzle basic_map.txt -h one
./npuzzle basic_map.txt -h misplacedtiles
./npuzzle basic_map.txt -h linearconflictplus
./npuzzle basic_map.txt -h one -b

A TESTER :
Fichier vide, sans permissions, et caetera
