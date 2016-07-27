/**
 * @file src/program/observer/observer.hpp
 * @author Adam 'Adanos' Gąsior
 * Used library: SFML 2.3.2
 */

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "../game/entity/Entity.hpp"

namespace rr {

/// Class for the observer
    class Observer {
    public: enum Event {
                ITEM_EQUIP_FAILURE,
                ITEM_DISCOVERED,
                ITEM_DROPPED,
                ITEM_PICKED,
                ITEM_USED,
                INVENTORY_FULL
            };

            virtual ~Observer() {}

            virtual void onNotify(Event, Entity*) = 0;
    };

/// Class for the subject
    class Subject {
    private: std::vector<Observer*> observers_;
    
    public: ~Subject();

             void addObserver   (Observer*);
             void removeObserver(Observer*);
             void clear         ();
             void notify        (Observer::Event, Entity*);
    };

}

#endif // OBSERVER_HPP