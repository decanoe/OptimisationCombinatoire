# OptimisationCombinatoire

# Contexte
L’objectif de ce projet est de réaliser des expériences scientifiques sur le problème de clique maximum d’un graphe (MCP) et sur sa version pondérée (WMCP). Dans un premier temps nous avons implémenté un Hill Climber avec un voisinage se basant sur une distance de Hamming. Ensuite, nous avons implémenté des heuristiques ainsi que des critères de choix pour le Hill Climber. Pour finir, nous avons réalisé une descente de gradient projeté. Ce rapport a pour objectif de présenter nos différentes expériences scientifiques réalisées.

# Utilisation
Pour recréer les résultats, un code main_exemple.cpp est fourni. Il suffit d'exécuter les commandes
- mkdir build
- cd build
- cmake ..
- make
- ./OptCombi

depuis la racine du projet pour le compiler et l’exécuter.
Ce fichier main_exemple.cpp donne un bon exemple de la façon de lancer chaque algorithme implémenté.
