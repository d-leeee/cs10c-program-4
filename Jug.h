#pragma once

#include <string>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::string;

const unsigned infinity = std::numeric_limits<unsigned>::max();

struct compareState {
    unsigned current;
    unsigned distance;
    bool operator>(const compareState& rhs) const {
        return distance > rhs.distance;
    }
};

struct State {
    unsigned a; // Amount in jug A
    unsigned b; // Amount in jug B

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
    string action;

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

class Jug {
    private:
        unsigned Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
        vector<State> states;

    public:
        // Constructor
        Jug(unsigned Ca, unsigned Cb, unsigned N, unsigned cfA, unsigned cfB, unsigned ceA, unsigned ceB, unsigned cpAB, unsigned cpBA) :
            Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {}

        /*
        // Rule of three
        ~Jug(); 
        Jug(const Jug&) = delete;
        Jug& operator=(const Jug&) = delete;
        */

        // Mutator functions
        int solve(string&); // Check input and find solution
                                  // Returns -1 if invalid input, empty string
                                  // Returns 0 if valid input but no solution
                                  // Returns 1 if solution found and stores solution steps in string
    private:
        unsigned stateNumber(unsigned, unsigned, unsigned, unsigned);
        void updateDistance(std::priority_queue<compareState, vector<compareState>, std::greater<compareState>>&, vector<State>& states, const unsigned&, const unsigned&, const unsigned&, const string& step);

};