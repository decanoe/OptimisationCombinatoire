#include "connexeGraphSize.hpp"
#include "../utils.hpp"
#include <iostream>

using namespace criteria;

double ConnexeGraphSize::evaluate(const Graph& g, const vector<vertex>& sub, const vector<vertex>& add, const vector<vertex>& rm) const {
    double score = 0;

    vector<bool> subBool(g.nb_vertices(),true);

    for (vertex n : rm){
        subBool[n] = false;
    }

    for (vertex n : sub){
        subBool[n] = false;
    }

    vector<vector<vertex>> sol;

    utils::connected_components(g,subBool,sol);

    for(vertex n : add){
        score += utils::dichotomy(sol, n).size();
    }
    return score;
}