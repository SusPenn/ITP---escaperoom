#ifndef RIDDLE_HPP
#define RIDDLE_HPP

#include "Timer.hpp"

class Riddle {
public:
    virtual ~Riddle() {}
    virtual bool solve() = 0;
    virtual void reset() = 0;
    virtual void displayClue() = 0;

protected:
    bool isSolved;
    Timer timer;
};

#endif // RIDDLE_HPP
