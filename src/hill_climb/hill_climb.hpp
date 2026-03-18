#pragma once

#include "../neighborhood/neighborhood.hpp"
#include "../criteria/criteria.hpp"

void hill_climb(const Graph& g, neighborhood::Neighborhood* neighborhood, criteria::Criteria* criteria, vector<vertex>& sub);