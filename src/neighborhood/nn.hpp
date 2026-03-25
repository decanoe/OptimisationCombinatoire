#pragma once

#include "neighborhood.hpp"

namespace neighborhood {
    class NN : public Neighborhood
    {
    protected:
        unsigned int N;

        bool check_add(const Graph& g, const vector<vertex>& sub, const vector<vertex>& to_add, const weight& score, vector<vertex>& best_to_add, weight& best_step_score, double& best_step_criteria) const;
        bool recursive_add_check(unsigned int n, const Graph& g, const vector<vertex>& sub, const vector<vertex>& direct_candidates, vector<vertex>& current_to_add, unsigned int next_candidate_index, const weight& current_score, vector<vertex>& best_to_add, weight& best_step_score, double& best_step_criteria) const;

        bool get_step(unsigned int n, const Graph& g, const vector<vertex>& sub, const vector<vertex>& direct_candidates, vector<vertex>& removed_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, const weight& current_score, weight& best_step_score, double& best_step_criteria) const;
        bool get_step(const Graph& g, const vector<vertex>& sub, const vector<vertex>& direct_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, const weight& current_score, weight& best_step_score, double& best_step_criteria) const override;
    public:
        NN(unsigned int N, criteria::Criteria* criteria, std::function<weight(const Graph &, vertex)> weights);
    };
}