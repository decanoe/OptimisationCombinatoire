#include "neighborhood.hpp"
#include "../utils.hpp"
#include <stdexcept>
using namespace neighborhood;

void Neighborhood::apply_step(const Graph& g, vector<vertex>& sub, const vector<vertex>& to_add, const vector<vertex>& to_remove) const {
    for (vertex v : to_remove) utils::remove_vertex(sub, v);
    for (vertex v : to_add) utils::insert_vertex(sub, v);
}
void Neighborhood::update_candidates(const Graph& g, const vector<vertex>& sub, vector<vertex>& candidates, const vector<vertex>& added, const vector<vertex>& removed) const {
    if (removed.size() != 0) {
        throw std::invalid_argument("removal is not implemented yet");

        for (vertex v : removed)
        {
            utils::insert_vertex(candidates, v);
        }
    }
    for (vertex v : added)
    {
        g.intersect_neighbors(candidates, v);
    }
}