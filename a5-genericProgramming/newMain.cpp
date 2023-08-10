#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Imatrix {
private:
    std::vector<std::vector<T>> data;

public:
    Imatrix() {}

    Imatrix(size_t rows, size_t cols)
        : data(rows, std::vector<T>(cols, T{})) {}

    T& operator()(size_t x, size_t y) {
        if (x >= data.size() || y >= data[0].size())
            throw std::out_of_range("Index out of range");
        return data[x][y];
    }

    const T& operator()(size_t x, size_t y) const {
        if (x >= data.size() || y >= data[0].size())
            throw std::out_of_range("Index out of range");
        return data[x][y];
    }

    Imatrix& operator=(const Imatrix& other) {
        data = other.data;
        return *this;
    }

    Imatrix& operator=(Imatrix&& other) noexcept {
        data = std::move(other.data);
        return *this;
    }

    Imatrix(const Imatrix& other)
        : data(other.data) {}

    Imatrix(Imatrix&& other) noexcept
        : data(std::move(other.data)) {}

    Imatrix operator+(const Imatrix& other) const {
        if (data.size() != other.data.size() || data[0].size() != other.data[0].size())
            throw std::invalid_argument("Matrix sizes do not match");

        Imatrix result(data.size(), data[0].size());
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Imatrix operator-(const Imatrix& other) const {
        if (data.size() != other.data.size() || data[0].size() != other.data[0].size())
            throw std::invalid_argument("Matrix sizes do not match");

        Imatrix result(data.size(), data[0].size());
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Imatrix operator*(const Imatrix& other) const {
        if (data[0].size() != other.data.size())
            throw std::invalid_argument("Matrix sizes are not compatible for multiplication");

        Imatrix result(data.size(), other.data[0].size());
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < other.data[0].size(); ++j) {
                result.data[i][j] = 0;
                for (size_t k = 0; k < data[0].size(); ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Imatrix operator/(const T& scalar) const {
        Imatrix result(data.size(), data[0].size());
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    std::vector<T> Row(size_t n) const {
        if (n >= data.size())
            throw std::out_of_range("Row index out of range");
        return data[n];
    }

    std::vector<T> Column(size_t n) const {
        if (data.empty() || n >= data[0].size())
            throw std::out_of_range("Column index out of range");

        std::vector<T> column;
        for (size_t i = 0; i < data.size(); ++i) {
            column.push_back(data[i][n]);
        }
        return column;
    }

    void Move(size_t x, size_t y) {
        if (x >= data.size() || y >= data[0].size())
            throw std::out_of_range("Index out of range");
        std::swap(data[x], data[y]);
    }
};

enum class PieceType {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

class Chess_piece {
private:
    PieceType type;
    bool is_white;

public:
    Chess_piece() : type(PieceType::EMPTY), is_white(true) {}
    Chess_piece(PieceType t, bool white) : type(t), is_white(white) {}

    PieceType get_type() const {
        return type;
    }

    bool is_white_piece() const {
        return is_white;
    }
};

int main() {
    try {
        // Testing Imatrix<int>
        Imatrix<int> int_matrix(2, 2);
        int_matrix(0, 0) = 1;
        int_matrix(0, 1) = 2;
        int_matrix(1, 0) = 3;
        int_matrix(1, 1) = 4;

        // Display int_matrix
        std::cout << "Matrix of ints:" << std::endl;
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 2; ++j) {
                std::cout << int_matrix(i, j) << " ";
            }
            std::cout << std::endl;
        }

        // Testing Imatrix<std::string>
        Imatrix<std::string> str_matrix(2, 2);
        str_matrix(0, 0) = "Hello";
        str_matrix(0, 1) = "World";
        str_matrix(1, 0) = "Aarhus";
        str_matrix(1, 1) = "University";

        // Display str_matrix
        std::cout << "\nMatrix of strings:" << std::endl;
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 2; ++j) {
                std::cout << str_matrix(i, j) << " ";
            }
            std::cout << std::endl;
        }

        // Testing Imatrix<Chess_piece>
        Chess_piece empty_piece(PieceType::EMPTY, true);
        Imatrix<Chess_piece> chess_matrix(2, 2);
        chess_matrix(0, 0) = empty_piece;
        Chess_piece pawn(PieceType::PAWN, true);
        Chess_piece knight(PieceType::KNIGHT, false);
        chess_matrix(0, 1) = pawn;
        chess_matrix(1, 0) = knight;

        // Display chess_matrix
        std::cout << "\nMatrix of Chess_pieces:" << std::endl;
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 2; ++j) {
                std::cout << static_cast<int>(chess_matrix(i, j).get_type()) << " ";
            }
            std::cout << std::endl;
        }

    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
