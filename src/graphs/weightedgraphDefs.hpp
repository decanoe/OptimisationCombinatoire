#pragma once
#include "graphDefs.hpp"
#include "graph.hpp"

weight getEdgeWeight  (const Graph & g, vertex v1, vertex v2);

weight getVertexWeight_mod(const Graph & g, vertex v);
weight getVertexWeight_1(const Graph & g, vertex v);
