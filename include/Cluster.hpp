#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include <vector>

#include "./Cell.hpp"

class Cluster {
   public:
    int ec, wc, qc;
    std::vector<Cell*> cells;
    int xc;

    Cluster(int _ec, int _wc, int _qc, int _xc);
    void addCel(Cell* cell, int xc);

    bool operator==(const Cluster& other) const {
        return ec == other.ec && wc == other.wc && xc == other.xc && cells == other.cells;
    }
};

#endif