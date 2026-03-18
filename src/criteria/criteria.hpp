#pragma once

#include "../graphs/graph.hpp"

namespace criteria{
    class Criteria{
        public:

            virtual double evaluate(const Graph& g, const vector<vertex>& sub, const vector<vertex>& add, const vector<vertex>& rm) const = 0;
    
    };
};