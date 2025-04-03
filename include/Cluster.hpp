#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include <vector>

#include "./Cell.hpp"

class Cluster {
   public:
    int ec, wc, qc;
    std::vector<Cell*> cells;
    int xc;

    Cluster(int _ec, int _wc, int _qc);
    void addCel(Cell* cell);

    bool operator==(const Cluster& other) const {
        return ec == other.ec && wc == other.wc && xc == other.xc && cells == other.cells;
    }
};

#endif