#pragma once
#include "Message.hpp"
#include <vector>

class Subscriber
{
public:
	Subscriber() = default;
	~Subscriber();

	virtual void Notify(const Message& aMessage) = 0;

	void Subscribe(const eMessageType& aMessageType);
	void Unsubscribe(const eMessageType& aMessageType);

private:
	std::vector<eMessageType> myMessagesSubscribedTo;

};

