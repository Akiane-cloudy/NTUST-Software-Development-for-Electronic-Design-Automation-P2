#ifndef LAYER_HPP
#define LAYER_HPP

#include <fstream>
#include <regex>

#include "./Row.hpp"

class Layer {
   public:
    static std::vector<Row> rows;               // List of rows
    static std::vector<Cell> cells;             // List of cells
    static std::vector<std::string> layerInfo;  // Some layer information
    static std::string filePath;                // Path to the file
    static std::string outputPath;              // Path to output .def file
    static int cellWidth;                       // Width of each cell
    static int cellHeight;                      // Height of each cell
    static double alpha;                        // Alpha value for the cost function

    static void init(std::string filePath, std::string outputPath, int cellWidth);  // Initialize the file path and cell width
    static void readFile();                                                         // Read the info from the file
    static void outputFile();
    static void setAlpha(double alpha);  // Set the alpha value for the cost function

    static void legalization();  // Legalize the cells
};

#endif