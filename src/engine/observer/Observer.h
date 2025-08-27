#pragma once

class Observer {
public:
	enum Action {
		KEY_PRESSED,
		KEY_RELEASED
	};
    virtual void Notify(int action, const int value) = 0;
    virtual ~Observer() {}
};