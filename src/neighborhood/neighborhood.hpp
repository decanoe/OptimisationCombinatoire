#pragma once

#include "../criteria/criteria.hpp"
#include "../graphs/graph.hpp"

namespace neighborhood {
    class Neighborhood
    {
    private:
    public:
        void apply_step(const Graph& g, vector<vertex>& sub, const vector<vertex>& to_add, const vector<vertex>& to_remove) const;
        void update_candidates(const Graph& g, const vector<vertex>& sub, vector<vertex>& candidates, const vector<vertex>& added, const vector<vertex>& removed) const;
        virtual bool get_step(const Graph& g, const vector<vertex>& sub, vector<vertex>& candidates, criteria::Criteria* criteria, vector<vertex>& to_add, vector<vertex>& to_remove) const = 0;
    };
}