#pragma once

#include "n1.hpp"

namespace neighborhood {
    class N2 : public N1
    {
    private:
    public:
        bool get_step(const Graph& g, const vector<vertex>& sub, vector<vertex>& candidates, criteria::Criteria* criteria, vector<vertex>& to_add, vector<vertex>& to_remove) const override;
    };
}