#pragma once

#include <string>

using std::string;

const unsigned infinity = std::numeric_limits<unsigned>::max();

class Jug {
    private:
        int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;

    public:
        // Constructor
        Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) :
            Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {}

        // Rule of three
        ~Jug();
        Jug(const Jug&) = delete;
        Jug& operator=(const Jug&) = delete;

        // Mutator functions
        int solve(const string&); // Check input and find solution
                                  // Returns -1 if invalid input, empty string
                                  // Returns 0 if valid input but no solution
                                  // Returns 1 if solution found and stores solution steps in string
    private:
        struct State {
            int a; // Amount in jug A
            int b; // Amount in jug B

            // Where to go on each of the six actions
            unsigned fillA;
            unsigned fillB;
            unsigned emptyA;
            unsigned emptyB;
            unsigned AtoB;
            unsigned BtoA;

            // These fields are useful when we do Dijkstra's method
            unsigned previous;
            unsigned distance;
            bool visited;

            State(unsigned a=infinity,
                unsigned b=infinity,
                unsigned fillA=infinity,
                unsigned fillB=infinity,
                unsigned emptyA=infinity,
                unsigned emptyB=infinity,
                unsigned AtoB=infinity,
                unsigned BtoA=infinity) :
                a(a),
                b(b),
                fillA(fillA),
                fillB(fillB),
                emptyA(emptyA),
                emptyB(emptyB),
                AtoB(AtoB),
                BtoA(BtoA),
                previous(infinity),
                distance(infinity),
                visited(false) {}
        };
};