#pragma once
#include "criteria.hpp"

namespace criteria{
    class ConnexeGraphSize : public Criteria{
        public:

            double evaluate(const Graph& g, const vector<vertex>& sub, const vector<vertex>& add, const vector<vertex>& rm) const;
        
    };
};