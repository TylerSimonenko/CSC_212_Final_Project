#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;
int main() {
    plt::plot({tn,tk,tb,});
    plt::show();
}
