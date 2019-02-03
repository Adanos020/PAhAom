#include <util/Observer.hpp>


namespace util
{

void Subject::addObserver(Observer* const o)
{
        observers.insert(o);
}

void Subject::send(const Message msg)
{
        for (Observer* o: observers)
        {
                o->receive(msg);
        }
}

}