#include "../include/Cluster.hpp"

Cluster::Cluster(int _ec, int _wc, int _qc) {
    ec = _ec;
    wc = _wc;
    qc = _qc;
    xc = 0;
}

void Cluster::addCel(Cell* cell) {
    cells.push_back(cell);

    ec += cell->weight;
    qc += cell->weight * (cell->x_globalPlacement - wc);
    wc += cell->width;
}
