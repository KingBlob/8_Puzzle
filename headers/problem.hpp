#ifndef __PROBLEM_HPP__
#define __PROBLEM_HPP__

class Problem {
    private:
        unsigned short *initial_state;
        unsigned short size;
        unsigned short blank_index;
        
    public:
        Problem();
        Problem(unsigned short* initial, unsigned short size);
        // Problem(Problem &);
        ~Problem();

        bool goal(); // True if initial_state = goal_state
        bool operator==(Problem const & rhs) const;
        
        unsigned short* getInitial(); // returns initial state
        unsigned short getSize() const; // returns size of the problem
        unsigned short getBlank(); // returns index of the blank tile
        // similar to the at() function in a vector, returns part of the state given an index
        unsigned short initialAt(int);

        void printState(); // Prints the array out nicely

        //Returns a new problem with move made or nullptr if move cannot be made
        Problem * Move(int dir);
        // Returns the size squared of the problem (8-puzzle would return 3x3=9)
        const int s2() const;

    private:
        unsigned short at(int) const;
        // Moves are classified by naming the way the blank space moves on the board
        Problem * up();
        Problem * down();
        Problem * left();
        Problem * right();
};

#endif /* __PROBLEM_HPP__ */