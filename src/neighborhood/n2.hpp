#pragma once

#include "n1.hpp"

namespace neighborhood {
    class N2 : public N1
    {
    protected:
        bool get_step(const Graph& g, const vector<vertex>& sub, const vector<vertex>& direct_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, const weight& current_score, weight& best_step_score, double& best_step_criteria) const override;
    public:
        N2(criteria::Criteria* criteria, std::function<weight(const Graph &, vertex)> weights);
    };
}