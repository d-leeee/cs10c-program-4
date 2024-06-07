#include "Jug.h"

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

unsigned Jug::stateNumber(const unsigned& a, const unsigned& b, const unsigned& Ca, const unsigned& Cb) const {
    return a * (Cb + 1) + b;
}

int Jug::solve(string& solution) {

    solution = "";

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

    vector<State> states;

    // Create every possible state in which the jugs can be in and add to vector
    for (unsigned a = 0; a <= Ca; a++) {
        for (unsigned b = 0; b <= Cb; b++) {

            // Fill state numbers
            unsigned fillA = stateNumber(Ca, b, Ca, Cb);
            unsigned fillB = stateNumber(a, Cb, Ca, Cb);
            
            // Empty state numbers
            unsigned emptyA = stateNumber(0, b, Ca, Cb);
            unsigned emptyB = stateNumber(a, 0, Ca, Cb);

            // Transfer state nunmbers
            unsigned transferFromA = min(a, Cb - b);
            unsigned AtoB = stateNumber(a - transferFromA, b + transferFromA, Ca, Cb);
            unsigned transferFromB = min(b, Ca - a);
            unsigned BtoA = stateNumber(a + transferFromB, b - transferFromB, Ca, Cb);
            
            // Emplace back new state into states vector
            states.emplace_back(a, b, fillA, fillB, emptyA, emptyB, AtoB, BtoA);
        }
    }

    // Dijkstra's method
    // Look for shortest path to n
    
    priority_queue<compareState, vector<compareState>, greater<compareState>> q;
    states[0].distance = 0;
    q.push({0, 0});

    while (!q.empty()) {

        unsigned current = q.top().current;
        q.pop();

        if (states[current].b == N && states[current].a == 0) {
            
            vector<string> steps;
            unsigned curr = current;
            
            while (curr != 0) {
                steps.push_back(states[curr].action);
                curr = states[curr].previous;
            }
            
            reverse(steps.begin(), steps.end());
            
            for (const string& step: steps) {
                solution += step + "\n";
            }

            solution += "success " + to_string(states[current].distance);

            return 1;
        }

        if (!states[current].visited) {
            
            states[current].visited = true;

            
            unsigned fillA = states[current].fillA;
            unsigned fillB = states[current].fillB;
            unsigned emptyA = states[current].emptyA;
            unsigned emptyB = states[current].emptyB;
            unsigned AtoB = states[current].AtoB;
            unsigned BtoA = states[current].BtoA;

            unsigned fillADistance = states[current].distance + cfA;
            unsigned fillBDistance = states[current].distance + cfB;
            unsigned emptyADistance = states[current].distance + ceA;
            unsigned emptyBDistance = states[current].distance + ceB;
            unsigned AtoBDistance = states[current].distance + cpAB;
            unsigned BtoADistance = states[current].distance + cpBA;

            updateDistance(q, states, fillA, fillADistance, current, "fill A");
            updateDistance(q, states, fillB, fillBDistance, current, "fill B");
            updateDistance(q, states, emptyA, emptyADistance, current, "empty A");
            updateDistance(q, states, emptyB, emptyBDistance, current, "empty B");
            updateDistance(q, states, AtoB, AtoBDistance, current, "pour A B");
            updateDistance(q, states, BtoA, BtoADistance, current, "pour B A");
        }
    }

    return 0;
}

void Jug::updateDistance(priority_queue<compareState, vector<compareState>, greater<compareState>>& q, vector<State>& states, const unsigned& currentDistance, const unsigned& cost, const unsigned& current, const string& step) {
    if (cost < states[currentDistance].distance) {
        states[currentDistance].distance = cost;
        states[currentDistance].previous = current;
        states[currentDistance].action = step;
        q.push({currentDistance, cost});
    }
}