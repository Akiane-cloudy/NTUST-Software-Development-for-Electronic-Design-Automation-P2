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

   public:
    std::list<Cluster> clusters;
    int x, y, x_min, x_max;
    static int cell_width;
    static int site_width;
    std::string name;
    std::string siteName;
    Orientation orientation;
    int xNum;
    int yNum;
    int xStep;
    int yStep;

    int cell_size;

    Row(Orientation _orientation, std::string _name, std::string _siteName, int _x, int _y, int _xNum, int _yNum, int _xStep, int _yStep);
    void addCell(Cell* cell);
    void placeRow(bool isFinal);
    double getCost(double alpha);
    void mergeCluster(Cluster* cluster1, Cluster* cluster2);
    void Collapse(std::list<Cluster>& clusters, std::list<Cluster>::iterator currentIt);
    void reset();
};

#endif