#include <chrono>

#include "../include/Layer.hpp"

int main(int argc, char** argv) {
    //./legalizer [cell width (in terms of sites)] [alpha] [input file name] [output file name]
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " [cell width] [alpha] [input file] [output file]" << std::endl;
        return 1;
    }
    int cellWidth = std::stoi(argv[1]);
    double alpha = std::stod(argv[2]);
    std::string inputFile = argv[3];
    std::string outputFile = argv[4];

    auto start_time = std::chrono::high_resolution_clock::now();

    Layer::init(inputFile, outputFile, cellWidth);
    Layer::setAlpha(alpha);
    Layer::readFile();
    Layer::legalization();
    Layer::outputFile();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration % std::chrono::minutes(1));
    std::cout << "Execution time: " << minutes.count() << " min and " << seconds.count() << " sec" << std::endl;

    return 0;
}