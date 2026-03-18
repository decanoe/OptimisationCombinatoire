#include "n1.hpp"
#include "../utils.hpp"

using namespace neighborhood;
using namespace criteria;

bool N1::get_step(const Graph &g, const vector<vertex> & sub, vector<vertex>& candidates, Criteria* criteria, vector<vertex>& to_add, vector<vertex>& to_remove) const {
    to_add.clear();
    to_remove.clear();
    if (candidates.size() == 0) return false; // local maxima reached

    vertex best = -1;
    double score = 0;
    for (vertex v : candidates)
    {
        double new_score = criteria->evaluate(g, sub, vector<vertex>(1, v), std::vector<vertex>());
        if (best == -1 || new_score > score) {
            score = new_score;
            best = v;
        }
    }

    to_add.push_back(best);
    return true; // HC can continue
}
/*bool N1::step(const Graph &g, vector<vertex> & sub, Criteria* criteria) const {
    vertex to_add = -1;
    double score = 0;

    std::vector<vertex>::iterator iter = sub.begin();
    for (vertex i = 0; i < g.nb_vertices(); i++)
    {
        if (iter != sub.end()) { // ignores vertices already presents in sub
            while (iter != sub.end() && *iter < i) iter++;
            if (iter != sub.end() && *iter == i) continue;
        }

        bool can_be_added = true;
        for (vertex v : sub)
        {
            if (!g.is_edge(i, v)) { can_be_added = false; break; }
        }
        if (can_be_added) {
            double new_score = criteria->evaluate(g, sub, vector<vertex>(1, i), std::vector<vertex>());
            if (to_add == -1 || new_score > score) {
                score = new_score;
                to_add = i;
            }
        }
    }

    if (to_add == -1) return false; // local maxima reached
    utils::insert_vertex(sub, to_add);
    return true; // HC can continue
}*/