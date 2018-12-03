Troisième règle :

La troisième règle fait rentrer la variable qui est entrée le moins de fois dans la base.
En cas d'égalité c'est la variable de plus petit indice qui rentre. J'ai pensé cette règle
de manière à éviter deux boucler sur un point dégénéré en me disant que cette règle devrait
empêcher d'alterner entre deux bases.
Finalement cette règle peut boucler sur des point dégénérés (par exemple sur coudert-example1).

Explication de mes exemples intéressants :

- example1 : C'este un exemple pour lequel l'algorithme du simplex dégénère si on utilise
	la règle MAXIMUM COEFFICIENT.