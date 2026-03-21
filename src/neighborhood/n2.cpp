#include "n2.hpp"
#include "../utils.hpp"
#include <iostream>

using namespace neighborhood;
using namespace criteria;

bool N2::get_step(const Graph &g, const vector<vertex> & sub, vector<vertex>& candidates, Criteria* criteria, vector<vertex>& to_add, vector<vertex>& to_remove) const {
    to_add.clear();
    to_remove.clear();
    if (candidates.size() == 0) return false; // local maxima reached

    vector<vertex> bestAdd;
    vector<vertex> bestRm;
    double score = 0;

    /*for (auto v : candidates) {
        cout << " " << v;
    }
    cout << endl;*/

    vector<vertex> copy_candidates = candidates;
    for (vertex vCandidate1: candidates){
        copy_candidates.erase(copy_candidates.begin());
        for (vertex vCandidate2: copy_candidates){
            vector<vertex> test_add;
            test_add.push_back(vCandidate1);
            test_add.push_back(vCandidate2);
            double new_score = criteria->evaluate(g, sub, test_add, std::vector<vertex>());
            if (bestAdd.size() == 0 || new_score > score) {
                score = new_score;
                bestAdd = test_add;
            }
        }
    }

    for (vertex vSub : sub){
        for (vertex vCandidate: candidates){
            vector<vertex> test_add = vector<vertex>(1,vCandidate);
            vector<vertex> test_rm = vector<vertex>(1,vSub);
            double new_score = criteria->evaluate(g, sub, test_add , test_rm);
            if (new_score > score) {
                score = new_score;
                bestAdd = test_add;
                bestRm = test_rm;
            }
        }
    }

    //cout << score<<endl;
    to_add = bestAdd;
    to_remove = bestRm;
    return true; // HC can continue
}