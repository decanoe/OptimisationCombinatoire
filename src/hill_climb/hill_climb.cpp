#include "hill_climb.hpp"

void hill_climb(const Graph& g, neighborhood::Neighborhood* neighborhood, criteria::Criteria* criteria, vector<vertex>& sub) {
    vector<vertex> candidates = vector<vertex>(g.nb_vertices());
    for (vertex i = 0; i < g.nb_vertices(); i++) candidates[i] = i;

    std::vector<vertex> to_add = std::vector<vertex>(), to_remove = std::vector<vertex>();
    while (neighborhood->get_step(g, sub, candidates, criteria, to_add, to_remove)) {
        neighborhood->update_sub_and_candidates(g, sub, candidates, to_add, to_remove);
    }
}