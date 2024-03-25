#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

class matrix {
private:
    double **matrix_;
    size_t size_;

    // Function for allocation memory
    void allocateMemory() {
        matrix_ = new double *[size_];
        for (int i = 0; i < size_; ++i) {
            matrix_[i] = new double[size_]{0};
        }
    }

    // Function for copying values
    void copyValues(matrix const &obj) {
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                matrix_[i][j] = obj.matrix_[i][j];
            }
        }
    }

    void freeMemory() {
        for (int i = 0; i < size_; ++i) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
        size_ = 0;
    }

public:
    // Beauty definition of matrix like {{1, 2, 3},
    //                                   {4, 5, 6},
    //                                   {7, 8, 9}}
    explicit matrix(size_t size,
           std::initializer_list<std::initializer_list<double>> init_matrix = {}):
           matrix_(nullptr), size_(size) {

        allocateMemory();

        double **p_str = matrix_;
        double *p_elm;
        for(std::initializer_list<double> str : init_matrix) {
            p_elm = *(p_str++);
            for(double num : str) {
                *(p_elm++) = num;
            }
        }
    }

    // General constructor
    matrix(size_t size, int len_arg, ...):
           matrix_(nullptr), size_(size) {

    }

    // Destructor
    ~matrix() {
        freeMemory();
    }

    // Copy constructor
    matrix(matrix const &obj): matrix_(nullptr), size_(obj.size_) {
        allocateMemory();
        copyValues(obj);
    }

    // Overload subscript operator
    double *operator[](int index) const {
        return matrix_[index];
    }

    // Overload assigned operator
    matrix &operator=(matrix const &obj) {
        if (this != &obj) {
            if (size_ != obj.size_) {
                freeMemory();
                size_ = obj.size_;
                allocateMemory();
            }
            copyValues(obj);
        }
        return *this;
    }

    // Overload multiply operator
    matrix operator*(double scalar) const {
        matrix temp = *this;
        temp.multiplyScalar(scalar);
        return temp;
    }

    friend matrix operator*(double scalar, matrix const &obj) {
        return obj * scalar;
    }

    // Print matrix
    void print() const {
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                std::cout << matrix_[i][j] << "  ";
            }
            std::cout << "\n";
        }
    }

public:
    // Matrix size
    [[nodiscard]] size_t size() const {
        return size_;
    }

    // Addition method
    void add(matrix const &obj) {
        if (size_ == obj.size_) {
            for (int i = 0; i < size_; ++i) {
                for (int j = 0; j < size_; ++j) {
                    matrix_[i][j] += obj.matrix_[i][j];
                }
            }
        }
    }

    // Multiply matrix method
    void multiplyMatrix(matrix const &obj) {
        if (size_ == obj.size_) {

            matrix temp(size_);

            for (int i = 0; i < size_; ++i) {
                for (int j = 0; j < size_; ++j) {
                    for (int k = 0; k < size_; ++k) {
                        temp.matrix_[i][j] +=
                                matrix_[i][k] * obj.matrix_[k][j];
                    }
                }
            }

            (*this) = temp;
        }
    }

    // Multiply scalar method
    void multiplyScalar(double scalar) {
        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                matrix_[i][j] *= scalar;
            }
        }
    }

    // Subtraction method
    void subtract(matrix const &obj) {
        if (size_ == obj.size_) {
            for (int i = 0; i < size_; ++i) {
                for (int j = 0; j < size_; ++j) {
                    matrix_[i][j] -= obj.matrix_[i][j];
                }
            }
        }
    }

    // Gauss method determinant
    double determinant() {
        matrix temp_matrix = *this;

        double coefficient = 0;
        for (int i = 0; i < temp_matrix.size_ - 1; i++) {
            for (int j = i + 1; j < temp_matrix.size_; j++) {

                coefficient = -temp_matrix[j][i] / temp_matrix[i][i];
                for (int k = 0; k < temp_matrix.size_; k++) {
                    temp_matrix[j][k] += temp_matrix[i][k] * coefficient;
                }
            }
        }

        double determinant = 1;
        for (int i = 0; i < temp_matrix.size_; ++i) {
            determinant *= temp_matrix[i][i];
        }

        return determinant;
    }

    // Transposed matrix
    void transposed() {
        matrix temp_matrix(size_);

        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {
                temp_matrix.matrix_[i][j] = matrix_[j][i];
            }
        }

        *this = temp_matrix;
    }

    // Reverse matrix
    void reverse() {
        double deter = determinant();
        if (deter == 0) return;

        matrix alg_matrix(size_);

        for (int i = 0; i < size_; ++i) {
            for (int j = 0; j < size_; ++j) {

                matrix minor(size_ - 1);

                std::vector<int> i_range(size_);
                //for (int k = 0; k < size_; ++k) { i_range[k] = k; };
                // Same
                std::iota(i_range.begin(), i_range.end(), 0);
                std::erase(i_range, i);

                std::vector<int> j_range(size_);
                //for (int k = 0; k < size_; ++k) { j_range[k] = k; };
                // Same
                std::iota(j_range.begin(), j_range.end(), 0);
                std::erase(j_range, j);

                for (int k = 0; k < size_ - 1; ++k) {
                    for (int l = 0; l < size_ - 1; ++l) {
                            minor[k][l] = matrix_[i_range[k]]
                                                 [j_range[l]];
                    }
                }

                alg_matrix[i][j] = minor.determinant() * pow(-1, i + j);
            }
        }

        alg_matrix.transposed();

        alg_matrix.multiplyScalar(1 / deter);

        *this = alg_matrix;
    }
};

int main() {
    matrix mat(3,  {{1, 5, 3},
                                  {4, 5, 6},
                                  {7, 8, 9}});


    //mat.reverse();
    mat.print();
    return 0;
}