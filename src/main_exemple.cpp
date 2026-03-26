
#include "graphs/graphListAdj.hpp"
#include "graphs/graphAdjMatrix.hpp"
#include "graphs/weightedgraphDefs.hpp"

#include <iostream>
#include "utils.hpp"
#include "runAllGraphs.hpp"

#include "hill_climb/hill_climb.hpp"
#include "criteria/degree.hpp"
#include "criteria/connexeGraphSize.hpp"
#include "neighborhood/nn.hpp"
#include "gradient/gradient.hpp"

int main(int argc , char* argv [])
{
    // chargement du graph
    string instance_path = "brock/brock200_1.clq";
    GraphHeavy g(instance_path);

    // ===================================================
    //              exécution gradient
    // ===================================================
    {
        // ========================== paramètres ==========================
        // pas du gradient
        weight step_size = .01;

        // nombre d'itérations
        unsigned int nb_iter = 2000;
        
        // fonction de poids (getVertexWeight_1 pour la version non pondérée, getVertexWeight_mod pour la pondérée)
        std::function<weight(const Graph &, vertex)> weights = &getVertexWeight_1; // getVertexWeight_1 ou getVertexWeight_mod

        // epsilon pour le poids d'une arête (aucune impacte mais doit être positif)
        weight epsilon = .01;

        // ========================== exécution ==========================
        cout<<"exécution gradient" << endl;
        vector<vertex> sub = vector<vertex>();
        weight score = gradient(g, weights, sub, step_size, epsilon, nb_iter);
        cout<<"clique maximale (" << score << ") :";
        utils::print_vector(cout, sub) << endl;

        // validation de la clique (au cas où)
        cout << "validation : " << (utils::is_clique(g, sub) ? "OK" : "Problème !") << "\n";
    }








    // ===================================================
    //              exécution hill_climb
    // ===================================================
    {
        // ========================== paramètres ==========================
        // taille du voisinage
        unsigned int N = 4;

        // critère de choix
        neighborhood::NN::Choice choice = neighborhood::NN::Choice::Best; // Best, Worst ou First
        
        // critère d'égalité
        criteria::Criteria* criteria = new criteria::Degree(); // Degree ou ConnexeGraphSize
        
        // fonction de poids (getVertexWeight_1 pour la version non pondérée, getVertexWeight_mod pour la pondérée)
        std::function<weight(const Graph &, vertex)> weights = &getVertexWeight_1; // getVertexWeight_1 ou getVertexWeight_mod

        // ========================== exécution ==========================
        cout<<"exécution hill climb" << endl;
        // création du voisinage
        neighborhood::Neighborhood* neigh = new neighborhood::NN(4, neighborhood::NN::Choice::Worst, new criteria::Degree(), &getVertexWeight_1);
        vector<vertex> sub = vector<vertex>();
        weight score = hill_climb(g, neigh, sub);
        cout<<"clique maximale (" << score << ") :";
        utils::print_vector(cout, sub) << endl;

        // validation de la clique (au cas où)
        cout << "validation : " << (utils::is_clique(g, sub) ? "OK" : "Problème !") << "\n";
    }

    return 0;
}
