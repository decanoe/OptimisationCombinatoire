
#include "graphs/graphListAdj.hpp"
#include "graphs/graphAdjMatrix.hpp"

#include <iostream>
#include "utils.hpp"

#include "hill_climb/hill_climb.hpp"
#include "criteria/degree.hpp"
#include "criteria/connexeGraphSize.hpp"
#include "neighborhood/n1.hpp"
#include "neighborhood/n2.hpp"

int main(int argc , char* argv [])
{
    //string s("myciel");
    string s("brock200_1.clq"); // nom de l'instance

    if (argc>=2) {
        s = argv[1];
        //s="../instances/"+s;
    }
    //GraphAdjMatrix g(s);
    GraphHeavy g(s);
    //GraphAdjVectorSorted g(s);
    //GraphAdjVector g(s);
    //GraphAdjVector g(100,0.8,2);
    //GraphAdjMatrix g(100,0.8,2);
    //GraphHeavy g(100,0.8,2);


    // Returns the density of the graph.
    cout<<"Nombre de sommets du graphe : " << g.nb_vertices()<<endl;
    cout<<"Nombre d arretes du graphe : " << utils::nb_edges(g)<<endl;
    cout<<"Densite du graphe : " << utils::density(g)<<endl;
    cout<<"Degre max du graphe : " << utils::max_degree(g)<<endl;
    cout<<"Parcours BFS du graphe partant de 0 : ";
    vector<vertex>  vertices_visit;
    utils::breadth_first_search(g,0,vertices_visit);
    utils::print_vector(cout, vertices_visit) << endl;
    vector<vector<vertex>> comp;
    utils::connected_components(g,   comp);
    for (auto a : comp) {
        cout<<"Composante connexe : ";
        utils::print_vector(cout, a) << endl;
        cout<<endl;
    }
    vector<vertex>  subset_vertices{0,1,2,55};
    utils::print_vector(cout, subset_vertices) << endl;
    utils::connected_components(g, subset_vertices,  comp);
    for (auto a : comp) {
        cout<<"Composante connexe : ";
        utils::print_vector(cout, a) << endl;
        //cout<<endl;
    }


    vector<vertex> sub = vector<vertex>();
    hill_climb(g, new neighborhood::N2(), new criteria::Degree(), sub);
    cout<<"clique maximale : ";
    utils::print_vector(cout, sub) << endl;

    cout << "validation : " << (utils::is_clique(g, sub) ? "OK" : "Problème !") << "\n";

    return 0;
}
