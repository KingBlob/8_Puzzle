#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "../headers/node.hpp"

using namespace std;

// Struct necessary to make the priority queue work with the Node class
// Compares the cost of 2 nodes to determine which one has the lowest
struct compareNodeCost{
    bool operator()(Node* lhs, Node* rhs) const {
        return (lhs->cost() > rhs->cost());
    }
};

// Performs a search over the starting state
// Inputs are a starting Problem and a search type
void Graph_Search(Problem &, unsigned short);
// Expands the Node popped from the frontier priority queue.
// Inputs are the Node expanded, the frontier, frontier set, and explored set.
void expand(Node *, priority_queue<Node*, vector<Node*>, compareNodeCost> &, vector<Problem*> &, vector<Problem*> &);
// Prints the steps of the solution by traversing the parent Nodes until it reaches the root.
void print_steps(Node *);

// Helper function that checks to see if the "set" (vector) has a Problem with an equivalent state.
bool set_contains(vector<Problem *> &, Problem *);
// Helper function used to remove the item from the frontier set if it was explored.
void pop_vect(Problem *, vector<Problem *> & v);


int main() {

    unsigned short n = 3;
    unsigned short search_type = 0;
    int puzzletype = 0;
    int inpt;
    unsigned short starting[] = {1,0,3,4,2,6,7,5,8};

    cout << "Welcome to 862241251 8 puzzle solver." << endl;
    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    cin >> puzzletype;

    if (puzzletype == 2) {
        cout << "Enter your puzzle, use a zero to represent the blank" << endl;
        cout << "Enter the first row, use a space or tabs between numbers     ";
        cin >> starting[0] >> starting[1] >> starting[2];
        cout << "Enter the second row, use space or tabs between numbers     ";
        cin >> starting[3] >> starting[4] >> starting[5];
        cout << "Enter the third row, use space or tabs between numbers     ";
        cin >> starting[6] >> starting[7] >> starting[8];
    }
    cout << endl;
    cout << "Enter your choice of algorithm" << endl;
    cout << "Uniform Cost Search" << endl;
    cout << "A* with the Misplaced Tile heuristic" << endl;
    cout << "A* with the Euclidean Distance heuristic" << endl;
    cin >> search_type;

    Problem starting_p(starting, n);
    starting_p.printState();
    Graph_Search(starting_p, search_type);

    return 1;
}



void Graph_Search(Problem & p, unsigned short search_type) {

    priority_queue<Node*, vector<Node*>, compareNodeCost> frontier;
    vector<Problem*> f_set;
    vector<Problem *> explored;

    Node * current = new Node(&p, 0, search_type, 0);
    frontier.push(current);
    f_set.push_back(current->getState());

    int nodes_expanded = 0;
    int max_frontier = 1;

    Node * solution = 0;
    while(true) {

        if (frontier.empty()) { break; }

        current = frontier.top();
        
        if (current->getState()->goal()) { solution = current; break; }

        explored.push_back(current->getState());
        expand(current, frontier, f_set, explored);

        nodes_expanded++;
        if (nodes_expanded%1000 == 0) {
            cout<<nodes_expanded<<". Frontier: "<<frontier.size()<<" f_set: "<<f_set.size()<<" cur_depth: "<<current->getDepth()<<endl;
        }
        max_frontier = max(max_frontier, int(frontier.size()));
    }
    if (solution) {
        print_steps(solution);
        cout << "\nTo solve this problem the search algorithm expanded a total of " << nodes_expanded << " nodes." << endl;
        cout << "The maximum number of nodes in queue at any one time: " << max_frontier << "." << endl;
        cout << "The depth of the goal node was " << solution->getDepth() << "." << endl;
    }
    else {
        cout << "No solution possible" << endl;
        cout << "\nTo solve this problem the search algorithm expanded a total of " << nodes_expanded << " nodes." << endl;
        cout << "The maximum number of nodes in queue at any one time: " << max_frontier << "." << endl;
    }
}

void expand(Node * cur, priority_queue<Node*, vector<Node*>, compareNodeCost> & f, vector<Problem*> & fs, vector<Problem *> & es) {
    unsigned short search_t = cur->getSearch();

    Problem * cur_state = cur->getState();

    f.pop();
    pop_vect(cur_state, fs);

    for (int i = 0; i < 4; i++) {
        Problem * cur_move = cur_state->Move(i);
        if (cur_move) {
            bool unique = true;
            // check explored set first then frontier set
            if (set_contains(es,cur_move)) {
                unique = false;
            }
            else {
                if (set_contains(fs, cur_move)) {
                    unique = false;
                }
            }
            if (unique) {
                Node * n = new Node(cur_move, cur, cur->getSearch(), cur->getDepth()+1);
                f.push(n);
                fs.push_back(n->getState());
            }
        }
    }
}

void print_steps(Node* sol) {

    if (sol->getParent()) {
        print_steps(sol->getParent());
        if(sol->getState()->goal()) { cout<< "Goal!!!"<<endl; }
        else {
            cout<< "The best state to expand with g(n) = "<<sol->getDepth()<<" and h(n) = "<<sol->heuristic()<<" is..."<<endl;
            sol->getState()->printState();
            cout<<"Expanding this node..."<<endl;
        }
    }
    else {
        cout<<"Expanding State"<<endl;
        sol->getState()->printState();
    }
}


// Helper function
bool set_contains(vector<Problem *> & check_set, Problem * val) {
    for (int i = 0; i < check_set.size(); i++) {
        int numequal = 0;
        if (val->getBlank() != check_set.at(i)->getBlank()) {
            continue;
        }
        for (int j = 0; j < val->s2(); j++) {
            if (val->initialAt(j) == check_set.at(i)->initialAt(j)) {
                numequal++;
            }
        }
        if (numequal == 9) {
            return true;
        }
    }
    return false;
}

void pop_vect(Problem * p, vector<Problem *> & v) {
    for (int i = 0; i < v.size(); i++) {
        if (p->getBlank() != v.at(i)->getBlank()) {
            continue;
        }
        int numequal = 0;
        for (int j = 0; j < p->s2(); j++) {
            if (p->initialAt(j) == v.at(i)->initialAt(j)) {
                numequal++;
            }
        }
        if (numequal == 9) {
            v.erase(v.begin() + i);
            return;
        }
    }
}