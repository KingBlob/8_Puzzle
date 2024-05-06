#include "../headers/node.hpp"

#include <iostream>
#include <cmath>
using namespace std;


Node::Node(){
    cout<<"Default Node"<<endl;
    this->parent = 0;
    this->state = 0;
    this->search = 0;
    this->depth = 0;
}

Node::Node(Problem *st, Node *p, unsigned short s, unsigned short d) {
    this->parent = p;
    this->state = st;
    this->search = s;
    this->depth = d;
}

Node::~Node() {
    delete this->state;
}

void Node::setParent(Node* par) {
    this->parent = par;
}

void Node::setState(Problem* st) {
    this->state = st;
}

void Node::setSearch(unsigned short srch) {
    this->search = srch;
}

void Node::setDepth(unsigned short dpt) {
    this->depth = dpt;
}

Node * Node::getParent() {
    return this->parent;
}

Problem * Node::getState() {
    return this->state;
}

unsigned short Node::getSearch() {
    return this->search;
}

unsigned short Node::getDepth() {
    return this->depth;
}

bool Node::operator==(Node & rhs) {
    return getState() == rhs.getState();
}

int Node::heuristic() {
    int retrn = 0;
    switch(getSearch()) {
        case 1:
            // Uniform cost search
            return 0;
        
        case 2:
            //misplaced tile heuristic
            for (int i = 0; i < getState()->s2(); i++) {
                if (getState()->getInitial()[i] == 0)
                    continue;
                if (getState()->getInitial()[i] != i+1)
                    retrn++;
            }
            return retrn;

        case 3:
            //euclidean distance heuristic
            for (int i = 0; i < getState()->getSize(); i++) {
                for (int j = 0; j < getState()->getSize(); j++) {
                    int x = getState()->getInitial()[(3*i + j)];
                    if (x == 0)
                        continue;
                    retrn += sqrt(pow((((x-1)/3)-i),2)+pow((int((x-1)%3)-j),2));
                }
            }
            return retrn;
    }
    return 0;
}

int Node::cost() {
    return getDepth() + heuristic();
}