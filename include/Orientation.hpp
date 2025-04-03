#ifndef ORIENTATION_HPP
#define ORIENTATION_HPP

#include <iostream>

enum class Orientation {
    N,
    S,
    E,
    W,
    FN,
    FS,
    FE,
    FW
};

inline std::ostream& operator<<(std::ostream& os, const Orientation& orientation) {
    switch (orientation) {
        case Orientation::N:
            os << "N";
            break;
        case Orientation::S:
            os << "S";
            break;
        case Orientation::E:
            os << "E";
            break;
        case Orientation::W:
            os << "W";
            break;
        case Orientation::FN:
            os << "FN";
            break;
        case Orientation::FS:
            os << "FS";
            break;
        case Orientation::FE:
            os << "FE";
            break;
        case Orientation::FW:
            os << "FW";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}

#endif