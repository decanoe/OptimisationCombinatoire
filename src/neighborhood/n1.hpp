#pragma once

#include "neighborhood.hpp"

namespace neighborhood {
    class N1 : public Neighborhood
    {
    private:
    public:
        bool step(const Graph& g, vector<vertex>& sub, criteria::Criteria* criteria) const;
    };
}