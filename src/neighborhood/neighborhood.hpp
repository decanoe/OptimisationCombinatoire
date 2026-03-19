#pragma once

#include "../criteria/criteria.hpp"
#include "../graphs/graph.hpp"

namespace neighborhood {
    class Neighborhood
    {
    private:
    public:
        void update_sub_and_candidates(const Graph& g, vector<vertex>& sub, vector<vertex>& candidates, const vector<vertex>& to_add, const vector<vertex>& to_remove) const;
        virtual bool get_step(const Graph& g, const vector<vertex>& sub, vector<vertex>& candidates, criteria::Criteria* criteria, vector<vertex>& to_add, vector<vertex>& to_remove) const = 0;
    };
}