#pragma once

#include "neighborhood.hpp"

namespace neighborhood {
    class N1 : public Neighborhood
    {
    private:
    public:
        bool get_step(const Graph& g, const vector<vertex>& sub, vector<vertex>& candidates, criteria::Criteria* criteria, vector<vertex>& to_add, vector<vertex>& to_remove) const;
    };
}