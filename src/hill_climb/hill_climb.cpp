#include "hill_climb.hpp"
#include "../utils.hpp"
#include <iostream>

weight hill_climb(const Graph& g, neighborhood::Neighborhood* neighborhood, vector<vertex>& sub) {
    vector<vertex> candidates = vector<vertex>(g.nb_vertices());
    for (vertex i = 0; i < g.nb_vertices(); i++) candidates[i] = i;

    std::vector<vertex> to_add = std::vector<vertex>(), to_remove = std::vector<vertex>();
    int iter = 0;
    weight score;
    while (neighborhood->get_step(g, sub, candidates, to_add, to_remove, score)) {
        neighborhood->update_sub_and_candidates(g, sub, candidates, to_add, to_remove);

        std::cout << "iteration " << iter++;
        utils::print_vector(cout << "\t+(", to_add) << ")";
        utils::print_vector(cout << "\t-(", to_remove) << ") \t=>" << score << endl;
    }
    return score;
}