#pragma once
#include "Message.hpp"

class Subscriber
{
public:
	virtual void Notify(Message aMessage) = 0;

private:

};

