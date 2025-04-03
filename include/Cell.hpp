#ifndef CELL_HPP
#define CELL_HPP

#include <iostream>

#include "./Orientation.hpp"

struct Cell {
    std::string name;
    std::string type;

    int x_globalPlacement;
    int y_globalPlacement;
    int x_legalization;
    int y_legalization;

    Orientation orientation;

    int width;
    int height;
    int weight = 1;

    Cell(std::string name, std::string type, int x_globalPlacement, int y_globalPlacement,
         int x_legalization, int y_legalization, Orientation orientation, int width, int height)
        : name(name),
          type(type),
          x_globalPlacement(x_globalPlacement),
          y_globalPlacement(y_globalPlacement),
          x_legalization(x_legalization),
          y_legalization(y_legalization),
          orientation(orientation),
          width(width),
          height(height) {}
    Cell() : name(""), type(""), x_globalPlacement(0), y_globalPlacement(0), x_legalization(0), y_legalization(0), orientation(Orientation::N), width(0), height(0) {}

    bool operator<(const Cell &other) const {
        return x_globalPlacement < other.x_globalPlacement;
    }
};

#endif