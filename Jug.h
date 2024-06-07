#pragma once

#include <string>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::string;
using std::priority_queue;
using std::greater;

const unsigned infinity = std::numeric_limits<unsigned>::max(); // Default distance of vertices should be infinity

// Comparison struct for min heap priority queue
struct compareState {
    unsigned current;                               // Current index
    unsigned distance;                              // Current distance to next vertex
    bool operator>(const compareState& rhs) const { // Compare current distance to new distance
        return distance > rhs.distance;
    }
};

// State struct for current state of water in jug
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
    unsigned previous; // Points to previous index (Used to find solution string when interating backwards)
    unsigned distance; // Distance to next vertex
    bool visited;      // If state was visited or not
    string action;     // Step as a string ("fillA", "empty B", etc)

    // Constructor for each state
    State (unsigned a=infinity,
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

// Assign the jug's capacities, goal, costs
class Jug {
    private:
        unsigned Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA; // Ca & Cb are the capacities of jugs a & b respectively
                                                            // N is the goal that jug b wants to reach (jug a will be empty)
                                                            // cfA, cfB are the costs to fill a jug
                                                            // ceA, ceB are the costs to empty a jug
                                                            // cpAB, cpBA are the costs to transfer water from one jug to another

        vector<State> states; // Stores every state the jugs could be in

    public:
        // Constructor
        Jug(const unsigned& Ca, 
            const unsigned& Cb, 
            const unsigned& N, 
            const unsigned& cfA, 
            const unsigned& cfB, 
            const unsigned& ceA, 
            const unsigned& ceB, 
            const unsigned& cpAB, 
            const unsigned& cpBA) :
            Ca(Ca), 
            Cb(Cb),
            N(N), 
            cfA(cfA), 
            cfB(cfB), 
            ceA(ceA), 
            ceB(ceB), 
            cpAB(cpAB), 
            cpBA(cpBA) {}

        // Mutator functions
        int solve(string&); // Check input and find solution
                            // Returns -1 if invalid input, empty string
                            // Returns 0 if valid input but no solution
                            // Returns 1 if solution found and stores solution steps in string
    private:
        // Helper functions
        const unsigned stateNumber(const unsigned&, const unsigned&, const unsigned&, const unsigned&) const ;   // Create state number of jugs
        void updateDistance(priority_queue<compareState, vector<compareState>, greater<compareState>>&,    // Find shortest distance and update 
            vector<State>& states, const unsigned&, const unsigned&, const unsigned&, const string& step);
        vector<State> createStates();                                                                      // Create every possible state
        bool validParameters() const;                                                                      // Check if parameters are valid                                                                            

};