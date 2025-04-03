#ifndef ROW_HPP
#define ROW_HPP

#include <algorithm>
#include <cmath>
#include <list>

#include "./Cluster.hpp"

class Row {
   private:
    double totalDisplacement;
    double maxDisplacement;
    int finalCellX;

   public:
    std::vector<Cell*> cells;
    int x, y, x_min, x_max;  // x_min and x_max are the min and max x position of the row;
    std::string name;
    std::string siteName;
    Orientation orientation;
    int xNum;
    int yNum;
    int xStep;
    int yStep;

    int cluster_final_pos;

    Row(Orientation _orientation, std::string _name, std::string _siteName, int _x, int _y, int _xNum, int _yNum, int _xStep, int _yStep);
    void addRow(Cell* cell);
    void placeRow(bool isFinal);
    double getCost(double alpha);
    void mergeCluster(Cluster* cluster1, Cluster* cluster2);
    void Collapse(std::list<Cluster>& clusters, std::list<Cluster>::iterator currentIt);
    void reset();
};

#endif