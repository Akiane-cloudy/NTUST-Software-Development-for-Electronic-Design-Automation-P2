#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include <vector>

#include "./Cell.hpp"

class Cluster {
   public:
    int ec, wc, qc;            // Total weight, total width, total something that to computer the optimal position;
    std::vector<Cell*> cells;  // Cells in the cluster;
    int xc;                    // Optimal x position;

    Cluster(int _ec, int _wc, int _qc);
    void addCel(Cell* cell);

    bool operator==(const Cluster& other) const {
        return ec == other.ec && wc == other.wc && xc == other.xc && cells == other.cells;
    }
};

#endif