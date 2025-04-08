#include "../include/Cluster.hpp"

Cluster::Cluster(int _ec, int _wc, int _qc, int _xc) {
    ec = _ec;
    wc = _wc;
    qc = _qc;
    xc = _xc;
}

void Cluster::addCel(Cell* cell, int xc) {
    cells.push_back(cell);

    ec += cell->weight;
    qc += cell->weight * (xc - wc);
    wc += cell->width;
}
