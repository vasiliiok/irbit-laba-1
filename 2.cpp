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
    static bool inversion(bool value_1) {
        return !value_1;
    }

    static bool conjunction(bool value_1, bool value_2) {
        return value_1 * value_2;
    }

    static bool disjunction(bool value_1, bool value_2) {
        return value_1 + value_2;
    }

    static bool implication(bool value_1, bool value_2) {
        return disjunction(conjunction(value_1, value_2),
                           inversion(value_1));
    }

    static bool coimplication(bool value_1, bool value_2) {
        return inversion(implication(value_1, value_2));
    }

    static bool exclusiveOr(bool value_1, bool value_2) {
        return disjunction(conjunction(value_1, inversion(value_2)),
                           conjunction(inversion(value_1), value_2));
    }

    static bool equals(bool value_1, bool value_2) {
        return inversion(exclusiveOr(value_1, value_2));
    }

    static bool pierceArrow(bool value_1, bool value_2) {
        return inversion(disjunction(value_1, value_2));
    }

    static bool schaefferStroke(bool value_1, bool value_2) {
        return inversion(conjunction(value_1, value_2));
    }
};

int main() {
    LogicalValuesArray obj(0);
    std::cout << !456;
}