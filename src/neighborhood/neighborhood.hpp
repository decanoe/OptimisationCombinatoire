#pragma once
#include <functional>

#include "../criteria/criteria.hpp"
#include "../graphs/graph.hpp"

namespace neighborhood {
    class Neighborhood
    {
    protected:
        criteria::Criteria* criteria;
        std::function<weight(const Graph &, vertex)> weights;

        virtual bool get_step(const Graph& g, const vector<vertex>& sub, vector<vertex>& direct_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, const weight& current_score, weight& best_step_score, double& best_step_criteria) const = 0;
    public:
        Neighborhood(criteria::Criteria* criteria, std::function<weight(const Graph &, vertex)> weights);

        void update_sub_and_candidates(const Graph& g, vector<vertex>& sub, vector<vertex>& direct_candidates, const vector<vertex>& to_add, const vector<vertex>& to_remove) const;
        bool get_step(const Graph& g, const vector<vertex>& sub, vector<vertex>& direct_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, weight& score) const;
    };
}