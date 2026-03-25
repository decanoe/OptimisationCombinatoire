#include "neighborhood.hpp"
#include "../utils.hpp"
#include <stdexcept>
#include <limits>
using namespace neighborhood;

Neighborhood::Neighborhood(criteria::Criteria* criteria, std::function<weight(const Graph &, vertex)> weights): criteria(criteria), weights(weights) {}

void Neighborhood::update_sub_and_candidates(const Graph& g, vector<vertex>& sub, vector<vertex>& direct_candidates, const vector<vertex>& to_add, const vector<vertex>& to_remove) const {
    for (vertex v : to_remove) utils::remove_vertex(sub, v);
    for (vertex v : to_add) utils::insert_vertex(sub, v);

    if (to_remove.size() != 0) {
        direct_candidates.clear();
        direct_candidates.resize(g.nb_vertices(), 0);
        for (vertex i = 0; i < g.nb_vertices(); i++) direct_candidates[i] = i;

        for (vertex v : sub)
        {
            g.intersect_neighbors(direct_candidates, v);
        }
    }
    else {
        for (vertex v : to_add)
        {
            g.intersect_neighbors(direct_candidates, v);
        }
    }
}

bool Neighborhood::get_step(const Graph& g, const vector<vertex>& sub, const vector<vertex>& direct_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, weight& score) const {
    double c = -std::numeric_limits<double>::max();
    weight start_score = score; 
    return this->get_step(g, sub, direct_candidates, to_add, to_remove, start_score, score, c);
}
