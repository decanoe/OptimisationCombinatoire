#pragma once

#include "../neighborhood/neighborhood.hpp"
#include "../criteria/criteria.hpp"

weight hill_climb(const Graph& g, neighborhood::Neighborhood* neighborhood, vector<vertex>& sub);