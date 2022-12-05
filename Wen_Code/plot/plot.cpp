#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
int main() {
    plt::plot({tn,tk,tb,});
    plt::show();
}
g++ minimal.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7
