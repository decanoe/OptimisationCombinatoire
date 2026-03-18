#pragma once

#include "../criteria/criteria.hpp"
#include "../graphs/graph.hpp"

namespace neighborhood {
    class Neighborhood
    {
    private:
    public:
        virtual bool step(const Graph& g, vector<vertex>& sub, criteria::Criteria* criteria) const = 0;
    };
}