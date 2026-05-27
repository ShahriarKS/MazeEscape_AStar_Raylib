#pragma once

struct Cell {
    int row;
    int col;

    bool operator==(const Cell& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Cell& other) const {
        return !(*this == other);
    }
};
