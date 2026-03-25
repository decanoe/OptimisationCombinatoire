#include "n1.hpp"
#include "../utils.hpp"

using namespace neighborhood;
using namespace criteria;

N1::N1(criteria::Criteria* criteria, std::function<weight(const Graph &, vertex)> weights): Neighborhood(criteria, weights) {}

bool N1::get_step(const Graph &g, const vector<vertex> & sub, const vector<vertex>& direct_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, const weight& current_score, weight& best_step_score, double& best_step_criteria) const {
    to_add.clear();
    to_remove.clear();
    if (direct_candidates.size() == 0) return false; // local maxima reached

    vertex best = -1;
    for (vertex v : direct_candidates)
    {
        weight test_score = current_score + this->weights(g, v);
        if (test_score < best_step_score) continue;
        
        double test_c_score = this->criteria->evaluate(g, sub, {v}, std::vector<vertex>());

        if (test_score > best_step_score || (test_c_score > best_step_criteria)) {
            best_step_score = test_score;
            best_step_criteria = test_c_score;
            best = v;
        }
    }

    if (best != -1) {
        to_add.push_back(best);
        return true; // HC can continue
    }

    return false; // indicated best_step_score was higher than anything found
}