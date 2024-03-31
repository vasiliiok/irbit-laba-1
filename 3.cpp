#include <iostream>
#include <cmath>

class Complex {
private:
    double real_;
    double imaginary_;

public:
    explicit Complex(double real = 0, double imaginary = 0):
        real_(real), imaginary_(imaginary) {}

public:
    void add(Complex const &obj) {
        real_ += obj.real_;
        imaginary_ += obj.imaginary_;
    }

    void subtract(Complex const &obj) {
        real_ -= obj.real_;
        imaginary_ -= obj.imaginary_;
    }

    void multiply(Complex const &obj) {
        double real = real_ * obj.real_ - imaginary_ * obj.imaginary_;
        double imaginary = real_ * obj.imaginary_ + imaginary_ * obj.real_;
        real_ = real;
        imaginary_ = imaginary;
    }

    void divide(Complex const &obj) {
        double divisor = obj.real_ * obj.real_ + obj.imaginary_ * obj.imaginary_;
        double real = (real_ * obj.real_ + imaginary_ * obj.imaginary_) / divisor;
        double imaginary = (imaginary_ * obj.real_ - real_ * obj.imaginary_) / divisor;
        real_ = real;
        imaginary_ = imaginary;
    }

    double abs() const {
        return std::sqrt(real_ * real_ + imaginary_ * imaginary_);
    }

    double argument() const {
        return std::atan2(imaginary_, real_);
    }
};

int main() {

}