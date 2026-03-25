#include "nn.hpp"
#include "../utils.hpp"

using namespace neighborhood;
using namespace criteria;

NN::NN(unsigned int N, criteria::Criteria* criteria, std::function<weight(const Graph &, vertex)> weights): N(N), Neighborhood(criteria, weights) {}


bool NN::check_add(const Graph& g, const vector<vertex>& sub, const vector<vertex>& to_add, const weight& score, vector<vertex>& best_to_add, weight& best_step_score, double& best_step_criteria) const {
    if (score < best_step_score) return false;
    
    double test_c_score = this->criteria->evaluate(g, sub, to_add, {});

    if (score > best_step_score || (test_c_score > best_step_criteria)) {
        best_step_score = score;
        best_step_criteria = test_c_score;
        best_to_add = to_add;
        return true;
    }
    return false;
}
bool NN::recursive_add_check(unsigned int n, const Graph& g, const vector<vertex>& sub, const vector<vertex>& direct_candidates, vector<vertex>& current_to_add, unsigned int next_candidate_index, const weight& current_score, vector<vertex>& best_to_add, weight& best_step_score, double& best_step_criteria) const {
    if (n == 0) return false;

    bool found_better = false;
    for (size_t i = next_candidate_index; i < direct_candidates.size(); i++)
    {
        bool can_add = true;
        for (vertex v : current_to_add) if (!g.is_edge(v, direct_candidates[i])) { can_add = false; break; }
        if (!can_add) continue;

        current_to_add.push_back(direct_candidates[i]);
        weight w = this->weights(g, direct_candidates[i]);

        found_better |= check_add(g, sub, current_to_add, current_score + w, best_to_add, best_step_score, best_step_criteria);

        found_better |= recursive_add_check(n-1, g, sub, direct_candidates, current_to_add, i+1, current_score + w, best_to_add, best_step_score, best_step_criteria);

        current_to_add.pop_back();
    }
    return found_better;
}

bool NN::get_step(unsigned int n, const Graph &g, const vector<vertex> & sub, const vector<vertex>& direct_candidates, vector<vertex>& removed_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, const weight& current_score, weight& best_step_score, double& best_step_criteria) const {
    // try add 1 to n vertices
    vector<vertex> temp = {};
    bool found_better = recursive_add_check(n, g, sub, direct_candidates, temp, 0, current_score, to_add, best_step_score, best_step_criteria);
    if (found_better) to_remove = {};
    
    // try removing 1 and calling NN with n-1
    // useless if n == 1 because we would remove 1 and add nothing (score would be worst)
    if (n > 1) {
        for (vertex removed_v : sub) {
            weight removed_weight = this->weights(g, removed_v);
            vector<vertex> new_sub = sub;
            utils::remove_vertex(new_sub, removed_v);
            removed_candidates.push_back(removed_v);
            
            vector<vertex> new_direct_candidates = vector<vertex>(g.nb_vertices(), 0);
            for (vertex i = 0; i < g.nb_vertices(); i++) new_direct_candidates[i] = i;
            
            for (vertex v : new_sub) g.intersect_neighbors(new_direct_candidates, v);
            for (vertex v : removed_candidates) utils::remove_vertex(new_direct_candidates, v);
            
            if (this->get_step(n-1, g, new_sub, new_direct_candidates, removed_candidates, to_add, to_remove, current_score - removed_weight, best_step_score, best_step_criteria)) {
                found_better = true;
                utils::insert_vertex(to_remove, removed_v);
            }

            removed_candidates.pop_back();
        }
    }
    return found_better;
}
bool NN::get_step(const Graph &g, const vector<vertex> & sub, const vector<vertex>& direct_candidates, vector<vertex>& to_add, vector<vertex>& to_remove, const weight& current_score, weight& best_step_score, double& best_step_criteria) const {
    to_add.clear();
    to_remove.clear();

    vector<vertex> removed_candidates = {};
    return this->get_step(this->N, g, sub, direct_candidates, removed_candidates, to_add, to_remove, current_score, best_step_score, best_step_criteria);
}