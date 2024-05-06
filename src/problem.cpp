#include "../headers/problem.hpp"
#include <iostream>
using namespace std;

Problem::Problem() {
    cout<<"default Problem()"<<endl;
}

Problem::Problem(unsigned short* initial, unsigned short s) {
    this->initial_state = initial;
    this->size = s;

    for (int i = 0; i < (s*s); i++){
        if (initial[i] == 0)
            blank_index = i;
    }
}

Problem::~Problem() {
    delete[] this->initial_state;
    cout<<"~Problem()"<<endl;
}


bool Problem::goal() {
    if (getBlank() != 8)
        return false;
    int numCorrect = 0;
    for (unsigned short i = 1; i < s2(); i++) {
        if (at(i-1) == i)
            numCorrect++;
    }
    if (numCorrect == 8)
        return true;
    else return false;
}

bool Problem::operator==(Problem const & rhs) const {
    int numsame = 0;
    for (int i = 0; i < s2(); i++) {
        if (at(i) == rhs.at(i)){
            numsame++;
        }
    }
    if (numsame == s2())
        return true;
    else return false;
}

void Problem::printState() {
    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < getSize(); j++) {
            cout << at(3*i + j)<< " ";
        }
        cout<<endl;
    }
}

// --- Getters ---

// Returns initial state
unsigned short * Problem::getInitial() {
    return this->initial_state;
}
// Returns size of the grid
unsigned short Problem::getSize() const {
    return this->size;
}
// Returns the index of the blank tile (useful for movement)
unsigned short Problem::getBlank() {
    return this->blank_index;
}

Problem * Problem::Move(int dir) {
    switch (dir){
        case 0:
            return up();
        case 1:
            return down();
        case 2:
            return left();
        case 3:
            return right();
        default:
            return 0;
    }
}


Problem * Problem::up() {
    if (getBlank()/getSize() > 0) {
        unsigned short * new_state = new unsigned short[s2()];
        for (int i = 0; i < s2(); i++) {
            new_state[i] = at(i);
        }
        new_state[getBlank()] = at(getBlank() - getSize());
        new_state[getBlank() - getSize()] = 0;
        return new Problem(new_state, getSize());
    }
    else return 0;
}

Problem * Problem::down() {
    if (getBlank()/getSize() < getSize() - 1) {
        unsigned short * new_state = new unsigned short[s2()];
        for (int i = 0; i < s2(); i++) {
            new_state[i] = at(i);
        }
        new_state[getBlank()] = at(getBlank() + getSize());
        new_state[getBlank() + getSize()] = 0;
        return new Problem(new_state, getSize());;
    }
    else return 0;
}
Problem * Problem::left() {
    if (getBlank()%getSize() != 0) {
        unsigned short * new_state = new unsigned short[s2()];
        for (int i = 0; i < s2(); i++) {
            new_state[i] = at(i);
        }
        new_state[getBlank()] = at(getBlank() - 1);
        new_state[getBlank() - 1] = 0;
        return new Problem(new_state, getSize());;
    }
    else return 0;
}
Problem * Problem::right() {
    if (getBlank()%getSize() != getSize() - 1) {
        unsigned short * new_state = new unsigned short[s2()];
        for (int i = 0; i < s2(); i++) {
            new_state[i] = at(i);
        }
        new_state[getBlank()] = at(getBlank() + 1);
        new_state[getBlank() + 1] = 0;
        return new Problem(new_state, getSize());;
    }
    else return 0;
}



unsigned short Problem::at(int i) const {
    return initial_state[i];
}

// Returns size squared, = getSize() * getSize()
const int Problem::s2() const {
    return size * size;
}

unsigned short Problem::initialAt(int i) {
    return initial_state[i];
}