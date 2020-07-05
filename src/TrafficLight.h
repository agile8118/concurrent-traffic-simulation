#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;
enum TrafficLightPhase { red, green };


template <class T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);

private:
    std::mutex _mutex;
    std::condition_variable _cond;
    std::deque<T> _queue;
};


class TrafficLight : public TrafficObject
{
public:

    // constructor / desctructor
    TrafficLight();
    
    // getters / setters
    TrafficLightPhase getCurrentPhase();

    // typical behaviour methods
    void waitForGreen();
    void simulate();

private:
    // typical behaviour methods
    void cycleThroughPhases();
    
    TrafficLightPhase _currentPhase;
    MessageQueue<TrafficLightPhase> _msgQ;
    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif
