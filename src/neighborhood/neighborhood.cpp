#include "neighborhood.hpp"
#include "../utils.hpp"
#include <stdexcept>
using namespace neighborhood;

void Neighborhood::update_sub_and_candidates(const Graph& g, vector<vertex>& sub, vector<vertex>& candidates, const vector<vertex>& to_add, const vector<vertex>& to_remove) const {
    for (vertex v : to_remove) utils::remove_vertex(sub, v);
    for (vertex v : to_add) utils::insert_vertex(sub, v);

    if (to_remove.size() != 0) {
        candidates.clear();
        candidates.resize(g.nb_vertices(), 0);
        for (vertex i = 0; i < g.nb_vertices(); i++) candidates[i] = i;

        for (vertex v : sub)
        {
            g.intersect_neighbors(candidates, v);
        }
    }
    else {
        for (vertex v : to_add)
        {
            g.intersect_neighbors(candidates, v);
        }
    }
}