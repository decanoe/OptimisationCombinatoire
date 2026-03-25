#include "n2.hpp"
#include "../utils.hpp"
#include <iostream>

using namespace neighborhood;
using namespace criteria;

/*
=====================================================================================
        Warning: This implementation does not work, please use NN instead !
=====================================================================================
*/

N2::N2(criteria::Criteria* criteria, std::function<weight(const Graph &, vertex)> weights): N1(criteria, weights) {
    std::cerr << "Warning: This implementation does not work, please use NN instead !";
}

bool N2::get_step(const Graph &g, const vector<vertex> & sub, const vector<vertex>& direct_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, const weight& current_score, weight& best_step_score, double& best_step_criteria) const {
    to_add.clear();
    to_remove.clear();

    vector<vertex> bestAdd;

    // try add 2
    if (direct_candidates.size() >= 2) {
        for (vertex v1: direct_candidates) {
            for (vertex v2: direct_candidates) {
                if (v2 <= v1) continue;
                if (!g.is_edge(v1, v2)) continue;

                weight test_score = current_score + this->weights(g, v1) + this->weights(g, v2);
                if (test_score < best_step_score) continue;
                
                vector<vertex> test_add = {v1, v2};
                double test_c_score = this->criteria->evaluate(g, sub, test_add, std::vector<vertex>());

                if (test_score > best_step_score || (test_c_score > best_step_criteria)) {
                    best_step_score = test_score;
                    best_step_criteria = test_c_score;
                    bestAdd = test_add;
                }
            }
        }
    }

    // try add 1
    if (N1::get_step(g, sub, direct_candidates, to_add, to_remove, current_score, best_step_score, best_step_criteria)) return true;

    if (bestAdd.size() != 0) {
        to_add = bestAdd;
        return true; // HC can continue
    }
    return false;
}