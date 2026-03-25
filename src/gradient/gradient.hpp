#pragma once
#include "../graphs/graph.hpp"
#include <functional>

weight gradient(const Graph& g,std::function<weight(const Graph&,vertex)> fweight,vector<vertex>& sub, float alpha = 0.01, float eps = 0.01,int iter = 2000);