#include "../include/Row.hpp"

Row::Row(Orientation _orientation, std::string _name, std::string _siteName,
         int _x, int _y, int _xNum, int _yNum, int _xStep, int _yStep) {
    totalDisplacement = 0;
    maxDisplacement = 0;
    finalCellX = 0;

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

void Row::addRow(Cell* cell) {
    cell->y_legalization = this->y;
    cell->orientation = this->orientation;
    this->cells.push_back(cell);
}

void Row::placeRow(bool isFinal) {
    std::list<Cluster> clusters;

    for (auto* cell : cells) {
        if (clusters.empty() ||
            clusters.back().xc + clusters.back().wc <= cell->x_globalPlacement) {
            int proposedX = cell->x_globalPlacement;
            int maxAllowedX = std::max(x_max - cell->width, x_min);
            int xc = std::clamp(proposedX, x_min, maxAllowedX);

            Cluster newCluster(0, 0, 0);
            newCluster.xc = xc;
            newCluster.addCel(cell);
            clusters.push_back(newCluster);
        } else {
            clusters.back().addCel(cell);
            Collapse(clusters, std::prev(clusters.end()));
        }
    }

    finalCellX = clusters.back().xc + clusters.back().wc;

    for (auto& cluster : clusters) {
        int xPos = cluster.xc;
        for (auto& cell : cluster.cells) {
            cell->x_legalization = xPos;
            if (isFinal) {
                cell->x_globalPlacement = xPos;
                cell->y_globalPlacement = this->y;
            }

            double displacement = std::sqrt(
                std::pow(cell->x_globalPlacement - cell->x_legalization, 2) +
                std::pow(cell->y_globalPlacement - cell->y_legalization, 2));

            totalDisplacement += displacement;
            maxDisplacement = std::max(maxDisplacement, displacement);
            xPos += cell->width;
        }
    }
}

double Row::getCost(double alpha) {
    double avgDisplacement = totalDisplacement / cells.size();
    return (finalCellX > x_max) ? 1e10 : (alpha * maxDisplacement + avgDisplacement);
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
        currentIt->xc = std::clamp(currentIt->xc, x_min, std::max(x_max - currentIt->wc, x_min));

        if (currentIt == clusters.begin()) {
            break;
        }

        auto prevIt = std::prev(currentIt);
        if (prevIt->xc + prevIt->wc > currentIt->xc) {
            mergeCluster(&(*prevIt), &(*currentIt));
            currentIt = clusters.erase(currentIt);
            currentIt = prevIt;
        } else {
            break;
        }
    }
}

void Row::reset() {
    totalDisplacement = 0;
    maxDisplacement = 0;
    finalCellX = 0;
}
