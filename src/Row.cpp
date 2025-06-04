#include "../include/Row.hpp"

int Row::cell_width = 0;
int Row::site_width = 0;

int alignToSite(int position) {
    return ((position + Row::site_width / 2) / Row::site_width) * Row::site_width;
}

Row::Row(Orientation _orientation, std::string _name, std::string _siteName, int _x, int _y, int _xNum, int _yNum, int _xStep, int _yStep) {
    totalDisplacement = 0;
    maxDisplacement = 0;
    cell_size = 0;

    orientation = _orientation;
    name = _name;
    siteName = _siteName;
    x = _x;
    y = _y;
    xNum = _xNum;
    yNum = _yNum;
    xStep = _xStep;
    yStep = _yStep;
    x_min = x;
    x_max = x + xNum * xStep;
}

void Row::addCell(Cell* cell) {
    cell_size += 1;
    cell->y_legalization = this->y;
    cell->orientation = this->orientation;

    int raw_position = std::clamp(cell->x_globalPlacement, x_min, std::max(x_max - cell->width, x_min));
    int valid_position = alignToSite(raw_position);
    valid_position = std::clamp(valid_position, x_min, std::max(x_max - cell->width, x_min)); 

    if (clusters.empty() || clusters.back().xc + clusters.back().wc <= valid_position) {
        Cluster newCluster(0, 0, 0, valid_position);
        newCluster.addCel(cell, valid_position);
        clusters.push_back(newCluster);
    } else {
        clusters.back().addCel(cell, valid_position);
        Collapse(clusters, std::prev(clusters.end()));
    }
}

void Row::placeRow(bool isFinal) {
    totalDisplacement = 0;
    maxDisplacement = 0;

    for (auto& cluster : clusters) {
        int xPos = cluster.xc;
        for (auto& cell : cluster.cells) {
            int tempX = xPos;

            if (isFinal) {
                cell->x_legalization = xPos;
                cell->x_globalPlacement = xPos;
                cell->y_globalPlacement = this->y;
            }

            double displacement =
                std::abs(cell->x_globalPlacement - tempX) +
                std::abs(cell->y_globalPlacement - cell->y_legalization);
            totalDisplacement += displacement;
            maxDisplacement = std::max(maxDisplacement, displacement);
            xPos += cell->width;
        }
    }
}

double Row::getCost(double alpha) {
    double avgDisplacement = totalDisplacement / cell_size;
    return (clusters.back().xc + clusters.back().wc > x_max) ? 1e10 : (alpha * maxDisplacement + avgDisplacement);
}

void Row::mergeCluster(Cluster* cluster1, Cluster* cluster2) {
    std::copy(cluster2->cells.begin(), cluster2->cells.end(), std::back_inserter(cluster1->cells));
    cluster1->ec += cluster2->ec;
    cluster1->qc += cluster2->qc - cluster2->ec * cluster1->wc;
    cluster1->wc += cluster2->wc;
}

void Row::Collapse(std::list<Cluster>& clusters, std::list<Cluster>::iterator currentIt) {
    while (true) {
        currentIt->xc = currentIt->qc / currentIt->ec;
        currentIt->xc = alignToSite(currentIt->xc);
        currentIt->xc = std::clamp(currentIt->xc, x_min, std::max(x_max - currentIt->wc, x_min)); // 再次夾住，避免 align 後超界

        if (currentIt == clusters.begin()) break;

        auto prevIt = std::prev(currentIt);
        if (prevIt->xc + prevIt->wc > currentIt->xc) {
            mergeCluster(&(*prevIt), &(*currentIt));
            currentIt = clusters.erase(currentIt);
            currentIt = prevIt;
        } else
            break;
    }
}

void Row::reset() {
    totalDisplacement = 0;
    maxDisplacement = 0;
}
