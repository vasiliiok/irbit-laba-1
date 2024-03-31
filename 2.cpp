#include <iostream>

class LogicalValuesArray {
private:
    unsigned int value_;

public:
    explicit LogicalValuesArray(unsigned int value = 0):
        value_(value) {};

    unsigned int getValue() {
        return value_;
    }

public:
    static bool inversion(unsigned int value_1) {
        return !value_1;
    }

    static bool conjunction(unsigned int value_1, unsigned int value_2) {
        return value_1 * value_2;
    }

    static bool disjunction(unsigned int value_1, unsigned int value_2) {
        return value_1 + value_2;
    }

    static bool implication(unsigned int value_1, unsigned int value_2) {
        return disjunction(conjunction(value_1, value_2),
                           inversion(value_1));
    }

    static bool coimplication(unsigned int value_1, unsigned int value_2) {
        return inversion(implication(value_1, value_2));
    }

    static bool exclusiveOr(unsigned int value_1, unsigned int value_2) {
        return disjunction(conjunction(value_1, inversion(value_2)),
                           conjunction(inversion(value_1), value_2));
    }

    static bool equals(unsigned int value_1, unsigned int value_2) {
        return inversion(exclusiveOr(value_1, value_2));
    }

    static bool pierceArrow(unsigned int value_1, unsigned int value_2) {
        return inversion(disjunction(value_1, value_2));
    }

    static bool schaefferStroke(unsigned int value_1, unsigned int value_2) {
        return inversion(conjunction(value_1, value_2));
    }

public:
    unsigned char getBit(unsigned int index) const {
        return value_ & (1u << index);
    }

    void write(char *pointer) {
        char *temp_pointer = pointer;
        for (int i = 0; i < sizeof(unsigned int) * 8; ++i) {
            *(temp_pointer++) = getBit(i);
        }
        *temp_pointer = 0;
    }
};

int main() {

}