#include "Jug.h"

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// Check input and find solution
// Returns -1 if invalid input, empty string
// Returns 0 if valid input but no solution
// Returns 1 if solution found and stores solution steps in string
int Jug::solve(string& solution) {

    solution = ""; // Set default solution

    // Check if input is valid
    if (!validParameters()) {
        return -1;
    }

    vector<State> states = createStates(); // Stores every possible state of jugs

    // Dijkstra's method
    // Look for shortest path to n
    
    priority_queue<compareState, vector<compareState>, greater<compareState>> q; // min heap priority queue
    states[0].distance = 0; // Set first state to 0
    q.push({0, 0});         // Push first state into queue

    // Traverse until the queue is empty
    while (!q.empty()) {

        unsigned current = q.top().current; // Highest priority 
        q.pop();                            // Remove lowest priority

        // If goal reached
        if (states[current].b == N && states[current].a == 0) {
            
            vector<string> steps;
            unsigned curr = current;
            
            // Traverse backwards till the first vertex and add each step
            while (curr != 0) {
                steps.push_back(states[curr].action);
                curr = states[curr].previous;
            }
            
            // Reverse the solution
            reverse(steps.begin(), steps.end());
            
            // Add each step to solution
            for (const string& step : steps) {
                solution += step + "\n";
            }

            // Add shortest length to solution
            solution += "success " + to_string(states[current].distance);

            return 1;
        }

        // If unvisited vertex
        if (!states[current].visited) {
            
            states[current].visited = true; // Vertex is now visisted

            // Current distance
            unsigned fillA = states[current].fillA;
            unsigned fillB = states[current].fillB;
            unsigned emptyA = states[current].emptyA;
            unsigned emptyB = states[current].emptyB;
            unsigned AtoB = states[current].AtoB;
            unsigned BtoA = states[current].BtoA;

            // Cost to next path
            unsigned fillADistance = states[current].distance + cfA;
            unsigned fillBDistance = states[current].distance + cfB;
            unsigned emptyADistance = states[current].distance + ceA;
            unsigned emptyBDistance = states[current].distance + ceB;
            unsigned AtoBDistance = states[current].distance + cpAB;
            unsigned BtoADistance = states[current].distance + cpBA;

            // Find shortest distance and update path
            updateDistance(q, states, fillA, fillADistance, current, "fill A");
            updateDistance(q, states, fillB, fillBDistance, current, "fill B");
            updateDistance(q, states, emptyA, emptyADistance, current, "empty A");
            updateDistance(q, states, emptyB, emptyBDistance, current, "empty B");
            updateDistance(q, states, AtoB, AtoBDistance, current, "pour A B");
            updateDistance(q, states, BtoA, BtoADistance, current, "pour B A");
        }

        // If no vertex found, exit
        if (states[current].distance == infinity) {
            cout << "Nobody left to visit." << endl;
            return 0;
        }
    }

    cout << "No solution found." << endl;
    return 0; 
}

// Find shortest distance and update 
void Jug::updateDistance(priority_queue<compareState, vector<compareState>, greater<compareState>>& q, vector<State>& states, const unsigned& currentDistance, const unsigned& cost, const unsigned& current, const string& step) {
    
    if (cost < states[currentDistance].distance) {
        states[currentDistance].distance = cost;
        states[currentDistance].previous = current;
        states[currentDistance].action = step;
        q.push({currentDistance, cost});
    }
}

// Create state number of jugs
const unsigned Jug::stateNumber(const unsigned& a, const unsigned& b, const unsigned& Ca, const unsigned& Cb) const {
    return a * (Cb + 1) + b;
}

// Create every possible state
vector<State> Jug::createStates() {

    vector<State> states; // Stores every possible state of jugs

    // Create every possible state in which the jugs can be in and add to vector
    for (unsigned a = 0; a <= Ca; a++) {
        for (unsigned b = 0; b <= Cb; b++) {

            // Fill state numbers
            unsigned fillA = stateNumber(Ca, b, Ca, Cb);
            unsigned fillB = stateNumber(a, Cb, Ca, Cb);
            
            // Empty state numbers
            unsigned emptyA = stateNumber(0, b, Ca, Cb);
            unsigned emptyB = stateNumber(a, 0, Ca, Cb);

            // Transfer state numbers
            unsigned transferFromA = min(a, Cb - b);
            unsigned AtoB = stateNumber(a - transferFromA, b + transferFromA, Ca, Cb);
            unsigned transferFromB = min(b, Ca - a);
            unsigned BtoA = stateNumber(a + transferFromB, b - transferFromB, Ca, Cb);
            
            // Emplace back new state into states vector
            states.emplace_back(a, b, fillA, fillB, emptyA, emptyB, AtoB, BtoA);
        }
    }
    return states;
}

// Check if parameters are valid
bool Jug::validParameters() const {

    // If negative capacities
    if (Ca <= 0 || Cb <= 0) {
        cout << "Capacity can't be negative." << endl;
        return false;
    }

    // If costs are negative
    else if (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpAB < 0) {
        cout << "Costs can't be negative." << endl;
        return false;
    }

    // If jug A is greater than jug B
    // If goal is greater than jug B
    // If jug B is greater than 1000
    else if (!(0 < Ca && Ca <= Cb) || !(N <= Cb && Cb <= 1000)) {
        cout << "Jug A and goal can't be greater than jug B, and jug B can't be greater than 1000." << endl;
        return false;
    }
}