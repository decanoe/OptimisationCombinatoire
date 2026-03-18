#include "degree.hpp"

using namespace criteria;

double Degree::evaluate(const Graph& g, const vector<vertex>& sub, const vector<vertex>& add, const vector<vertex>& rm) const {
    double score = 0;
    for (vertex n : add){
        score += g.degree(n);
    }

    for (vertex n : rm){
        score -= g.degree(n);
    }

    return score;
}
        