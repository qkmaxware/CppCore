#ifndef _SYSTEM_EVENT_HPP
#define _SYSTEM_EVENT_HPP

namespace System {
namespace Event {

/**
 * Templated class that models an object that observes another 
 */
template <typename T>
class IObserver {
    private:
    public:
        /**
         * Recieve an update for an observed quantity after the given event has passed 
         */
        virtual void Update(int event, T& observable) = 0;
};

/**
 * Class that represents an object that can be observed 
 */
template <typename T>
class IObservable {
    private:
    public:
        /**
         * Add an observer to this observable for the given event 
         */
        virtual void Attach(int event, IObserver<T>* observer) = 0;
        /**
         * Remove an observer from this observable for the given event 
         */
        virtual void Detach(int event, IObserver<T>* observer) = 0;
        /**
         * Notify observers of this event that the observable may have changed 
         */
        virtual void Notify(int event) = 0;
};

}
}

#endif