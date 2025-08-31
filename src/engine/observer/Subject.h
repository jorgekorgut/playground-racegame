#pragma once
#include "Observer.h" 
#include <vector>
#include <iostream>

class Subject {
public:
    virtual void Attach(std::shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
	}

    virtual void Detach(std::shared_ptr<Observer> observer)
    {
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    virtual void Notify(int action, void* value)
    {
        for(auto observer : observers) 
        {
            observer->Notify(action, value);
		}
    };
    virtual ~Subject() {}

private :
	std::vector<std::shared_ptr<Observer>> observers;
};