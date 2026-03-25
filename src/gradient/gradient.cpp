#include "gradient.hpp"
#include "../utils.hpp"
#include "../graphs/weightedgraphDefs.hpp"
#include <iostream>
#include <algorithm>

void step_gradient(const Graph& g,std::function<weight(const Graph&,vertex)> weight,vector<float>& z, float alpha, float eps){
    for (vertex v1 = 0; v1 < g.nb_vertices(); v1++){
        float sum = 0.0;
        for (vertex v2 = 0; v2 < g.nb_vertices(); v2++){
            if(v1 != v2 && !g.is_edge(v1,v2)){
                sum += (std::min(weight(g,v1),weight(g,v2)) + eps) * z[v2];
            }
        }
        z[v1] = std::max(0.f,std::min(1.f,z[v1] + alpha * (weight(g,v1) - sum)));
    }
}

void gradient(const Graph& g,std::function<weight(const Graph&,vertex)> weight,vector<vertex>& sub, float alpha, float eps,int iter){
    vector<float> z = vector<float>(g.nb_vertices(), 0);
    
    for (unsigned int i = 0; i<iter; i++){
        step_gradient(g,weight,z,alpha,eps);
    }

    auto max = std::max_element(z.begin(),z.end());
    while (*max > 0)
    {
        int index = std::distance(z.begin(),max);
        z[index] = 0;

        bool insert = true;

        for(vertex v : sub){
            if(!g.is_edge(v,index)){
                insert = false;
                break;
            }
        }
        if(insert){
            utils::insert_vertex(sub,index);
        }
        max = std::max_element(z.begin(),z.end());
    }

}