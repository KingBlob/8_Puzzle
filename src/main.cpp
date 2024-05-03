#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include "../headers/node.hpp"

using namespace std;

struct compareNodeCost{
    bool operator()(Node* lhs, Node* rhs) const {
        return (lhs->cost() < rhs->cost());
    }
};
struct compareNodeEquality {
    bool operator()(Problem * lhs, Problem * rhs) const {
        return (*lhs == *rhs);
    }
};

// void expand(Node &, priority_queue<Node, vector<Node>, compareNodeCost> &, set<Node,compareNodeEquality> &, set<Node,compareNodeEquality>&);
void expand(Node *, priority_queue<Node*, vector<Node*>, compareNodeCost> &, vector<Node*> &, set<Problem*,compareNodeEquality> &);
Node * Graph_Search(Problem &, unsigned short);
void print_steps(Node *);


int main() {
    // unsigned short starting[] = {1,0,3,4,2,6,7,5,8};
    unsigned short starting[] = {1,2,3,0,5,6,4,7,8};
    // unsigned short goalst[] = {1,2,3,4,5,6,7,8,0};

    unsigned short n = 3;
    unsigned short search_type = 0;

    Problem starting_p(starting, n);
    Node * solution = Graph_Search(starting_p, search_type);

    if (solution) {
        print_steps(solution);
    }
    else {
        cout << "No solution possible" << endl;
    }

    return 1;
}



Node * Graph_Search(Problem & p, unsigned short search_type) {

    priority_queue<Node*, vector<Node*>, compareNodeCost> frontier;
    // set<Node,compareNodeEquality> frontier_set;
    vector<Node*> f_set;
    set<Problem *,compareNodeEquality> explored;

    Node * current = new Node(&p, 0, search_type, 0);
    frontier.push(current);
    f_set.push_back(current);
    // frontier_set.insert(root);

    while(true) {

        if (frontier.empty()) { return 0; }

        current = frontier.top();
        cout<<"Initial state:"<<endl;
        current->getState()->printState();
        
        if (current->getState()->goal()) { return current; }

        explored.insert(current->getState());
        cout<<"expanding..."<<endl;
        expand(current, frontier, f_set, explored);
        cout<<"Frontier size: "<<frontier.size()<<endl;
        // expand(current, frontier, explored);
    }
}
// void expand(Node & cur, priority_queue<Node, vector<Node>, compareNodeCost> & f, set<Node,compareNodeEquality> & e, set<Node,compareNodeEquality> &fs) {
void expand(Node * cur, priority_queue<Node*, vector<Node*>, compareNodeCost> & f, vector<Node*> & fs, set<Problem *,compareNodeEquality> & e) {
    unsigned short search_t = cur->getSearch();

    Problem * cur_state = cur->getState();
    f.pop();

    for (int i = 0; i < 4; i++) {
        if (cur_state->Move(i)) {
            cout<<"i: "<<i<<"  depth: "<<cur->getDepth()<<endl;
            cur_state->Move(i)->printState();
            bool unique = true;
            // check explored set first then frontier set
            if (e.count(cur_state)) {
                unique = false;
            }
            else {
            // checking frontier for the state
            // could be an issue: can't have same state with different
            // costs here, so might get incorrect cost.
                for (int i = 0; i < fs.size(); i++) {
                    if (cur_state->Move(i) == fs.at(i)->getState()) {
                        unique = false;
                        break;
                    }
                }
            }
            if (unique) {
                Node * n = new Node(cur_state->Move(i), cur, cur->getSearch(), cur->getDepth()+1);
                f.push(n);
                fs.push_back(n);
            }
        }
    }
}

void print_steps(Node* sol) {
    for (Node * i = sol; i; i=i->getParent()) {
        i->getState()->printState();
        cout<<endl;
    }
}