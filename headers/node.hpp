#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "problem.hpp"

class Node {
    private:
        Node * parent;
        Problem * state;
        unsigned short search;
        unsigned short depth;
    
    public:
        Node();
        Node(Problem * state, Node * parent, unsigned short search, unsigned short depth);
        ~Node();

        void setParent(Node*);
        void setState(Problem*);
        void setSearch(unsigned short);
        void setDepth(unsigned short);

        Node * getParent();
        Problem * getState();
        unsigned short getSearch();
        unsigned short getDepth();

        bool operator==(Node &);

        int heuristic();
        int cost();
};


#endif /* __NODE_HPP__ */