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
        
        unsigned short* getInitial();
        unsigned short getSize() const;
        unsigned short getBlank();
        unsigned short initialAt(int);

        void printState();

        //Returns a new problem with move made or nullptr if move cannot be made
        Problem * Move(int dir);
        const int s2() const;

    private:
        unsigned short at(int) const;
        Problem * up();
        Problem * down();
        Problem * left();
        Problem * right();
};

#endif /* __PROBLEM_HPP__ */