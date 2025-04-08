#include "../include/Layer.hpp"

std::vector<Row> Layer::rows;
std::vector<Cell> Layer::cells;
std::vector<std::string> Layer::layerInfo;
std::string Layer::filePath = "";
std::string Layer::outputPath = "";
int Layer::cellWidth = 0;
int Layer::cellHeight = 0;
double Layer::alpha = 0.0;

void Layer::init(std::string filePath, std::string outputPath, int cellWidth) {
    Layer::cellWidth = cellWidth;
    Layer::filePath = filePath;
    Layer::outputPath = outputPath;
}

void Layer::readFile() {
    std::ifstream in(filePath);
    std::vector<Cell> cells;
    std::vector<Row> rows;

    static std::regex cellRegex(R"(COMPONENTS\s+(\d+)\s*;)");
    static std::regex cellPattern(R"(-\s+(\w+)\s+(\w+)\s+\+\s+PLACED\s+\(\s*(\-*\d+)\s+(\-*\d+)\s*\)\s+(N|S|E|W|FN|FS|FE|FW)\s*;)");
    static std::regex rowPattern(R"(ROW\s+(\w+)\s+(\w+)\s+(\d+)\s+(\d+)\s+(N|S|E|W|FN|FS|FE|FW)\s+\DO\s+(\d+)\s+BY\s+(\d+)\s+STEP\s+(\d+)\s+(\d+)\s*;)");
    std::smatch match;

    for (std::string input; std::getline(in, input);) {
        if (std::regex_search(input, match, cellRegex)) {
            int totalComponents = std::stoi(match[1]);
            for (int i = 0; i < totalComponents; ++i) {
                std::getline(in, input);
                if (std::regex_search(input, match, cellPattern)) {
                    std::string name = match[1];
                    std::string type = match[2];
                    int x_globalPlacement = std::stoi(match[3]);
                    int y_globalPlacement = std::stoi(match[4]);
                    int x_legalization = x_globalPlacement;
                    int y_legalization = y_globalPlacement;
                    Orientation orient;

                    auto getOrientation = [](const std::string &orientStr) {
                        if (orientStr == "N") return Orientation::N;
                        if (orientStr == "S") return Orientation::S;
                        if (orientStr == "E") return Orientation::E;
                        if (orientStr == "W") return Orientation::W;
                        if (orientStr == "FN") return Orientation::FN;
                        if (orientStr == "FS") return Orientation::FS;
                        if (orientStr == "FE") return Orientation::FE;
                        if (orientStr == "FW") return Orientation::FW;
                        throw std::invalid_argument("Invalid orientation");
                    };

                    orient = getOrientation(match[5]);
                    cells.emplace_back(name, type, x_globalPlacement, y_globalPlacement, x_legalization, y_legalization, orient, cellWidth, cellHeight);
                }
            }
        } else if (std::regex_search(input, match, rowPattern)) {
            std::string rowName = match[1];
            std::string siteName = match[2];
            int x = std::stoi(match[3]);
            int y = std::stoi(match[4]);

            auto getOrientation = [](const std::string &orientStr) {
                if (orientStr == "N") return Orientation::N;
                if (orientStr == "S") return Orientation::S;
                if (orientStr == "E") return Orientation::E;
                if (orientStr == "W") return Orientation::W;
                if (orientStr == "FN") return Orientation::FN;
                if (orientStr == "FS") return Orientation::FS;
                if (orientStr == "FE") return Orientation::FE;
                if (orientStr == "FW") return Orientation::FW;
                throw std::invalid_argument("Invalid orientation");
            };

            Orientation orient = getOrientation(match[5]);
            int xNum = std::stoi(match[6]);
            int yNum = std::stoi(match[7]);
            int xStep = std::stoi(match[8]);
            int yStep = std::stoi(match[9]);

            rows.emplace_back(orient, rowName, siteName, x, y, xNum, yNum, xStep, yStep);
            if (!cellHeight) cellHeight = std::abs(rows[0].y - rows[1].y);
        } else {
            layerInfo.push_back(input);
        }
    }

    Layer::cells = cells;
    Layer::rows = rows;
    Row::cell_width = cellWidth;
}

void Layer::outputFile() {
    std::ofstream out(outputPath);

    for (int i = 0; i < 8; i++) {
        out << layerInfo[i] << '\n';
    }

    for (auto &row : rows) {
        out << "ROW ";
        out << row.name << " " << row.siteName << " " << row.x << " " << row.y << " " << row.orientation << " DO " << row.xNum << " BY " << row.yNum << " STEP " << row.xStep << " " << row.yStep << ";" << std::endl;
    }
    out << "\n";

    out << "COMPONENTS " << cells.size() << ";" << std::endl;
    for (auto &cell : cells) {
        out << "- " << cell.name << " " << cell.type << " + PLACED (" << cell.x_legalization << " " << cell.y_legalization << ") " << cell.orientation << ";" << std::endl;
    }
    out << "END COMPONENTS" << "\n\n";

    out << "END DESIGN";
}

void Layer::setAlpha(double alpha) {
    Layer::alpha = alpha;
}

void Layer::legalization() {
    std::sort(cells.begin(), cells.end());
    for (auto &cell : cells) {
        double best_cost = std::numeric_limits<double>::max();
        Row *best_row = nullptr;
        auto copy_cell = cell;

        for (auto &row : rows) {
            auto copy_clusters = row.clusters;

            row.addCell(&cell);
            row.placeRow(false);

            double cost = row.getCost(alpha);
            if (cost < best_cost) {
                best_cost = cost;
                best_row = &row;
            }

            row.reset();
            row.clusters = copy_clusters;
            row.cell_size -= 1;
            cell = copy_cell;
        }

        if (best_row) {
            best_row->addCell(&cell);
            best_row->placeRow(true);
        }
    }
}
