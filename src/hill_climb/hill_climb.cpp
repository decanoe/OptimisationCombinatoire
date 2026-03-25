#include "hill_climb.hpp"
#include "../utils.hpp"
#include <iostream>

void hill_climb(const Graph& g, neighborhood::Neighborhood* neighborhood, criteria::Criteria* criteria, vector<vertex>& sub) {
    vector<vertex> candidates = vector<vertex>(g.nb_vertices());
    for (vertex i = 0; i < g.nb_vertices(); i++) candidates[i] = i;

    std::vector<vertex> to_add = std::vector<vertex>(), to_remove = std::vector<vertex>();
    int iter = 0;
    while (neighborhood->get_step(g, sub, candidates, criteria, to_add, to_remove)) {
        std::cout << "iteration " << iter++;
        std::cout << "\n\tadd ";
        utils::print_vector(to_add);
        std::cout << "\tremove ";
        utils::print_vector(to_remove);

        neighborhood->update_sub_and_candidates(g, sub, candidates, to_add, to_remove);
    }
}