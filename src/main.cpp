#include <iostream>
#include <queue>
#include <vector>
// #include <set>
#include "../headers/node.hpp"

using namespace std;

struct compareNodeCost{
    bool operator()(Node* lhs, Node* rhs) const {
        return (lhs->cost() > rhs->cost());
    }
};
// struct compareNodeEquality {
//     bool operator()(Problem * lhs, Problem * rhs) const {
//         return (*lhs == *rhs);
//     }
// };

// void expand(Node &, priority_queue<Node, vector<Node>, compareNodeCost> &, set<Node,compareNodeEquality> &, set<Node,compareNodeEquality>&);
void expand(Node *, priority_queue<Node*, vector<Node*>, compareNodeCost> &, vector<Problem*> &, vector<Problem*> &);
void Graph_Search(Problem &, unsigned short);
void print_steps(Node *);

bool set_contains(vector<Problem *> &, Problem *);


int main() {
    unsigned short starting[] = {1,0,3,4,2,6,7,5,8};
    // unsigned short starting[] = {1,2,3,0,5,6,4,7,8};
    // unsigned short starting[] = {1,2,3,4,5,6,7,0,8};
    // unsigned short goalst[] = {1,2,3,4,5,6,7,8,0};

    unsigned short n = 3;
    unsigned short search_type = 3;

    Problem starting_p(starting, n);
    Graph_Search(starting_p, search_type);

    return 1;
}



void Graph_Search(Problem & p, unsigned short search_type) {

    priority_queue<Node*, vector<Node*>, compareNodeCost> frontier;
    // set<Node,compareNodeEquality> frontier_set;
    vector<Problem*> f_set;
    vector<Problem *> explored;

    Node * current = new Node(&p, 0, search_type, 0);
    frontier.push(current);
    f_set.push_back(current->getState());
    // frontier_set.insert(root);

    int nodes_expanded = 0;
    int max_frontier = 1;

    Node * solution = 0;
    while(true) {

        if (frontier.empty()) { break; }

        current = frontier.top();
        // cout<<"Initial state:"<<endl;
        // current->getState()->printState();
        
        if (current->getState()->goal()) { solution = current; break; }

        explored.push_back(current->getState());
        // cout<<"expanding..."<<endl;
        expand(current, frontier, f_set, explored);
        // cout<<"Frontier size: "<<frontier.size()<<endl;
        // expand(current, frontier, explored);
        nodes_expanded++;
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
    }
}
// void expand(Node & cur, priority_queue<Node, vector<Node>, compareNodeCost> & f, set<Node,compareNodeEquality> & e, set<Node,compareNodeEquality> &fs) {
void expand(Node * cur, priority_queue<Node*, vector<Node*>, compareNodeCost> & f, vector<Problem*> & fs, vector<Problem *> & es) {
    unsigned short search_t = cur->getSearch();

    Problem * cur_state = cur->getState();
    f.pop();

    for (int i = 0; i < 4; i++) {
        if (cur_state->Move(i)) {
            // cout<<"i: "<<i<<"  depth: "<<cur->getDepth()<<"  cost: "<<cur->cost()<<endl;
            // cur_state->Move(i)->printState();
            bool unique = true;
            // check explored set first then frontier set
            if (set_contains(es,cur_state->Move(i))) {
                unique = false;
            }
            else {
            // checking frontier for the state
            // could be an issue: can't have same state with different
            // costs here, so might get incorrect cost.
                if (set_contains(fs, cur_state->Move(i))) {
                    unique = false;
                }
            }
            if (unique) {
                Node * n = new Node(cur_state->Move(i), cur, cur->getSearch(), cur->getDepth()+1);
                f.push(n);
                fs.push_back(n->getState());
            }
        }
    }
}

void print_steps(Node* sol) {
    // for (Node * i = sol; i; i=i->getParent()) {
    //     i->getState()->printState();
    //     cout<<endl;
    // }

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
        // cout<<"Does ";
        // val->printState();
        // cout<<"Equal ";
        // check_set.at(i)->printState();
        for (int j = 0; j < val->s2(); j++) {
            if (val->getInitial()[j] != check_set.at(i)->getInitial()[j]) {
                numequal++;
            }
        }
        if (numequal == 9) {
            // cout<<"Yes"<<endl;
            return true;
        }
        // cout<<"No"<<endl;
    }
    return false;
}