#include "n2.hpp"
#include "../utils.hpp"

using namespace neighborhood;
using namespace criteria;

bool N2::get_step(const Graph &g, const vector<vertex> & sub, vector<vertex>& candidates, Criteria* criteria, vector<vertex>& to_add, vector<vertex>& to_remove) const {
    to_add.clear();
    to_remove.clear();

    vector<vertex> bestAdd;
    vector<vertex> bestRm;
    double score = 0;

    // try add 2
    if (candidates.size() >= 2) {
        for (vertex v1: candidates) {
            for (vertex v2: candidates) {
                if (v2 <= v1) continue;
                if (!g.is_edge(v1, v2)) continue;
                
                vector<vertex> test_add = {v1, v2};
                double new_score = criteria->evaluate(g, sub, test_add, std::vector<vertex>());
                if (bestAdd.size() == 0 || new_score > score) {
                    score = new_score;
                    bestAdd = test_add;
                }
            }
        }
        if (bestAdd.size() != 0) {
            to_add = bestAdd;
            to_remove = bestRm;
            return true; // HC can continue
        }
    }

    // try add 1
    if (N1::get_step(g, sub, candidates, criteria, to_add, to_remove)) return true; // HC can continue

    // try remove 1 and add 1
    // for (vertex vSub : sub){
    //     for (vertex vAdd = 0; vAdd < g.nb_vertices(); vAdd++) {
    //         if (utils::contains(sub, vAdd)) continue;

    //         bool can_be_added = true;
    //         for (vertex v : sub)
    //         {
    //             if (vSub != v && !g.is_edge(vAdd, v)) {
    //                 can_be_added = false;
    //                 break;
    //             }
    //         }
    //         if (!can_be_added) continue;
            
    //         vector<vertex> test_add = {vAdd};
    //         vector<vertex> test_rm = {vSub};
    //         double new_score = criteria->evaluate(g, sub, test_add , test_rm);
    //         if (bestAdd.size() == 0 || new_score > score) {
    //             score = new_score;
    //             bestAdd = test_add;
    //             bestRm = test_rm;
    //         }
    //     }
    // }
    // if (bestAdd.size() != 0) {
    //     to_add = bestAdd;
    //     to_remove = bestRm;
    //     return true; // HC can continue
    // }

    return false; // local maxima reached
}