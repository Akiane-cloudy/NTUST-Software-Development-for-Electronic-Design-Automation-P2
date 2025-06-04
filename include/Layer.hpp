#ifndef LAYER_HPP
#define LAYER_HPP

#include <fstream>
#include <regex>

#include "./Row.hpp"

class Layer {
   public:
    static std::vector<Row> rows;
    static std::vector<Cell> cells;
    static std::vector<std::string> layerInfo;
    static std::string filePath;
    static std::string outputPath;
    static int cellWidth; // site unit
    static int cellHeight;
    static double alpha;
    static int siteWidth;

    static void init(std::string filePath, std::string outputPath, int cellWidth);
    static void readFile();
    static void outputFile();
    static void setAlpha(double alpha);

    static void legalization();
};

#endif