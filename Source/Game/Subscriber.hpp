#pragma once
#include "Message.hpp"
#include <vector>

class Subscriber
{
public:
	Subscriber() = default;
	~Subscriber();

	virtual void Notify(Message aMessage) = 0;

	void Subscribe(eMessageType aMessageType);
	void Unsubscribe(eMessageType aMessageType);

private:
	std::vector<eMessageType> myMessagesSubscribedTo;

};

