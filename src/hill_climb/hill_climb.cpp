#include "hill_climb.hpp"

void hill_climb(const Graph& g, neighborhood::Neighborhood* neighborhood, criteria::Criteria* criteria, vector<vertex>& sub) {
    while (neighborhood->step(g, sub, criteria));
}