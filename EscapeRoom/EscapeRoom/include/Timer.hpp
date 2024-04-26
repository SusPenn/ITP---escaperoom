#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
public:
    Timer();
    void start();
    void update();
    bool isTimeUp() const;

private:
    float startTime;
    float duration;
    bool isRunning;
};

#endif // TIMER_HPP
