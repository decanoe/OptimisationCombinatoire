#include "weightedgraphDefs.hpp"

weight getEdgeWeight  (const Graph & g, vertex v1, vertex v2){
     return std::min((v2-v1)*(v2-v1),(g.nb_vertices()+std::min(v1,v2)-std::max(v1,v2))*(g.nb_vertices()+std::min(v1,v2)-std::max(v1,v2)));
}

weight getVertexWeight_mod(const Graph & g, vertex v){
    return 1 + v % 200;
}
weight getVertexWeight_1(const Graph & g, vertex v){
    return 1;
}
