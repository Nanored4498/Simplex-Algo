# Comment ça marche ?

Afin de compiler il suffit de tapper `make`.  
Ensuite `make tests` permet de générer tous les fichiers de sortie pour tous les fichiers
.dat qui sont dans le dossier `tests`, le tout avec la règle de BLAND. Enfin `make clean`
supprime tous les fichiers créés.

Vous pouvez taper `./coudert-exec -h` pour savoir comment marche l'exécutable.
Exemple d'utilisation : `./coudert-exec -b -v tests/coudert-example1.dat
permet de d'utiliser l'algorithme du simplex avec la règle de Bland en mode verbose sur
le fichier d'exemple donné en dernier argument

Les fichiers :

- gen_bad_bland.py
- gen_klee_minty.py
- gen_random.py

permettent de générer de nouveaux exemples en leur passant en argumant une dimension d,
c'est à dire le nombre de variables. Pour le générateur aléatoire il faut aussi passer
en argument le nombre de contraintes. D'ailleurs ce générateur ne crée que des contraintes
dont le right-hand side est positif si la valeur de la variable neq_rh est à False.

Le fichier [gen_tests.py](gen_tests.py) permet de générer un fichier indiquant les dimensions d'exemples
aléatoires à tester afin d'évaluer les performances. Le fichier commence par 6 paramètres
à ajuster. On peur alors taper :  
```bash
./gen_tests.py | ./test_perf
```  
afin d'ajouter les résultats des tests dans le fichier [perf.txt](perf.txt).
Finalement [affichage.py](affichage.py) permet d'afficher ces résultats en affichant le logarithme du temps
passer en moyenne pour chaques dimensions de tests aléatoires.
On remarque qu'on a presque :  
	log(t) = n * m / 760 - 3.4  
	donc t = exp(n * m / 760 - 3.4) secondes  
A part les limites liées au temps d'exécution je n'ai pas rencontré de limitations.

## Sensibilité

Finalement lorsqu'on regarde les tranches du nuages de points on remarque qu'à nombre de variables
fixé, la courbe est bombé (concave) alors qu'à nombre de contraintes fixé la courbe est à peu près
linéaire. Ainsi le programme senmble plus sensible au nombre de contraintes lorsqu'il a beaucoup
de variables et peu de contraintes. Mais lorsque il y a un nombre de contraintes assez similaire
au nombre de variables ce sont le programme est plus sensibles au nombre de variables.

# Détails sur les fractions

Comme on peut le voire j'ai écris une classe Fraction. Mais en testant sur mes exemples aléatoires,
j'ai pu observer des overflows. C'est pourquoi j'ai décidé de refaire la classe en utilisant `mpq_t`
de GMP. On peut toujours revenir à mon ancienne classe en changeant la définition de la variable de
prépocessing `VERSION` à 0 dans le fichier [fraction.h](fraction.h). Elle est actuellement à 1 pour la version
qui utilise `mpq_t`.

# Règles :

## Troisième règle

La troisième règle fait rentrer la variable qui est entrée le moins de fois dans la base.
En cas d'égalité c'est la variable de plus petit indice qui rentre. J'ai pensé cette règle
de manière à éviter deux boucler sur un point dégénéré en me disant que cette règle devrait
empêcher d'alterner entre deux bases.
Finalement cette règle peut boucler sur des point dégénérés (par exemple sur coudert-example1).

## Diférence entre les règles

Seule la règle de BLAND est assurée de s'arrêter parmis les 3. On peut aussi remarquer que la règle
MAXIMUM est plus rapide sur les exemples générés aléatoirement. Plus il y a de variables plus la
différence est net. Par exemple pour `coudert-random5`, MAXIMUM RULE fait 70 pivots alors que
BLAND'S RULE FAIT 605 pivots.

# Explication de mes exemples intéressants :

- example1 : C'est un exemple pour lequel l'algorithme du simplex dégénère et boucle à l'infini
	si on utilise la règle MAXIMUM COEFFICIENT ou ma règle.
- example2 : C'est un exemple qui est un pire cas pour MAXIMUM RULE, qui nécessite aussi beaucoup
	de pivot pour BLAND'S RULE et qui est normal pour ma règle.
- example3 : C'est un exemple qui se fait en un pivot pour MAXIMUM RULE mais qui nécessite le
	nombre de variables pivots pour BLAND'S RULE et ma règle.
- example4 : C'est un tout petit exemple à une variable et une contraintes afin de tester qu'il n'y
	a pas d'imprévus avec de petits nombres. Et c'est aussi un simplex unbouded.
- Dans les exemples aléatoires on retrouve deux exemple avec 40 variables et 80 contraintes, l'un
	avec des coefficients positifs et l'autre avec aussi des coefficients négatifs. On trouve aussi
	des exemples avec 60 variables et 50 contraintes, 20 variables et 500 contraintes et un dernier
	avec 200 variables et 20 contraintes.