#pragma once

#include "neighborhood.hpp"

namespace neighborhood {
    class N1 : public Neighborhood
    {
    protected:
        virtual bool get_step(const Graph& g, const vector<vertex>& sub, vector<vertex>& direct_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, const weight& current_score, weight& best_step_score, double& best_step_criteria) const override;
    public:
        N1(criteria::Criteria* criteria, std::function<weight(const Graph &, vertex)> weights);
    };
}