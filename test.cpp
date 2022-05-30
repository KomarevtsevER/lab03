#include "histogram.h"
#include "SVG.h"
#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void
test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void
test_similar() {
    double min = 0;
    double max = 0;
    find_minmax({2, 2, 2}, min, max);
    assert(min == 2);
    assert(max == 2);
}

void
test_one() {
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void
test_pustoi() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

void
test_1() {
vector<double> numbers = {1, 3, 1, 3};
size_t bin_count = 2;
vector <double> otvet = {1, 1};
assert(bin_size (numbers, bin_count)==otvet);
}

void
test_2() {
vector<double> numbers = {1};
size_t bin_count = 1;
vector <double> otvet = {0, 1};
assert(bin_size (numbers, bin_count)==otvet);
}

int
main() {
    test_positive();
    test_negative();
    test_similar();
    test_one();
    test_pustoi();
    test_1();
    test_2();
}
