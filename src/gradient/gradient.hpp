#pragma once
#include "../graphs/graph.hpp"
#include <functional>

void gradient(const Graph& g,std::function<weight(const Graph&,vertex)> weight,vector<vertex>& sub, float alpha = 0.01, float eps = 0.01,int iter = 2000);