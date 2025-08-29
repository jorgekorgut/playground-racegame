#pragma once

class Observer {
public:
	enum Action {
		KEY_PRESSED,
		KEY_RELEASED,
		MOUSE_MOVED,
		MOUSE_BUTTON
	};
    virtual void Notify(int action, void * value = nullptr) = 0;
    virtual ~Observer() {}
};