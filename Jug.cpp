#include "Jug.h"
#include <vector>

int Jug::solve(const string& solution) {

    // Check valid input

    // If empty capacities
    if (Ca <= 0 || Cb <= 0) {
        return -1;
    }

    // If costs are negative
    else if (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpAB < 0) {
        return -1;
    }

    // If jug A is greater than jug B
    // If goal is greater than jug B
    // If jug B is greater than 1000
    else if (!(0 < Ca && Ca <= Cb) || !(N <= Cb && Cb <= 1000)) {
        return -1;
    }

    std::vector<State> states;

    for (unsigned a = 0; a <= Ca; a++) {
        for (unsigned b = 0; b <= Cb; b++) {

            unsigned fillA = 
        }
    }

}