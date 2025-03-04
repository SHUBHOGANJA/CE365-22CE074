#include <iostream>
#include <unordered_map>
#include <set>
#include <string>
using namespace std;

bool validateString(
    const unordered_map<int, unordered_map<char, int>> &transitions,
    int startState,
    const set<int> &acceptStates,
    const string &input
) {
    int currentState = startState;
    for (char c : input) {
        if (transitions.find(currentState) != transitions.end() &&
            transitions.at(currentState).find(c) != transitions.at(currentState).end()) {
            currentState = transitions.at(currentState).at(c); 
        }
        else {
            return false; 
        }
    }
    return acceptStates.find(currentState) != acceptStates.end();
}

int main() {
    unordered_map<int, unordered_map<char, int>> transitions;
    set<int> acceptStates;
    int numStates, numTransitions, startState;

    cout << "Enter the number of states: ";
    cin >> numStates;

    cout << "Enter the start state: ";
    cin >> startState;

    int numAcceptStates;
    cout << "Enter the number of accept states: ";
    cin >> numAcceptStates;

    cout << "Enter the accept states: ";
    for (int i = 0; i < numAcceptStates; ++i) {
        int state;
        cin >> state;
        acceptStates.insert(state);
    }

    cout << "Enter the number of transitions: ";
    cin >> numTransitions;

    cout << "Enter transitions in the format: <current_state> <input_char> <next_state>\n";
    for (int i = 0; i < numTransitions; ++i) {
        int currentState, nextState;
        char inputChar;
        cin >> currentState >> inputChar >> nextState;
        transitions[currentState][inputChar] = nextState;
    }
    string input;
    cout << "Enter a string to validate: ";
    cin >> input;
    if (validateString(transitions, startState, acceptStates, input)) {
        cout << "Valid String" << endl;
    }
    else {
        cout << "Invalid String" << endl;
    }
    return 0;
}
/* tt for 011 :
Number of states: 4
Start state: 0
Accept state(s): 3
Transitions:
0 0 1
0 1 0
1 1 2
2 1 3
3 0 1
3 1 3
*/
/*
*/
