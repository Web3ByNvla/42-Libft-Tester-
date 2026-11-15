# Testeur Libft

Petit testeur maison pour vérifier les fonctions de ma Libft. Quand une
fonction standard existe, le résultat est comparé à celui de la libc. Les
autres fonctions sont vérifiées avec quelques résultats attendus.

Les tests couvrent les fonctions de caractères, les chaînes, la mémoire, les
listes chaînées et les fonctions d’écriture sur des descripteurs de fichiers.

## Utilisation

Depuis ce dossier :

```sh
make
make run
```

Le testeur affiche `OK` ou `FAIL` pour chaque cas. `make run` renvoie un code
d’erreur si au moins un test échoue.

Pour supprimer l’exécutable :

```sh
make clean
```

Le Makefile utilise la bibliothèque située dans `../Libft_42`.
