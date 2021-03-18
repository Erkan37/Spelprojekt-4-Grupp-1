#include "stdafx.h"
#include "Subscriber.hpp"
#include "PostMaster.hpp"

Subscriber::~Subscriber()
{
	for (eMessageType& messageType : myMessagesSubscribedTo)
	{
		Unsubscribe(messageType);
	}
}

void Subscriber::Subscribe(eMessageType aMessageType)
{
	for (eMessageType& messageType : myMessagesSubscribedTo)
	{
		if (messageType == aMessageType) return;
	}

	myMessagesSubscribedTo.push_back(aMessageType);
	PostMaster::GetInstance().AddSubcriber(this, aMessageType);
}

void Subscriber::Unsubscribe(eMessageType aMessageType)
{
	for (size_t messageTypeIndex = 0; messageTypeIndex < myMessagesSubscribedTo.size(); ++messageTypeIndex)
	{
		if (myMessagesSubscribedTo[messageTypeIndex] == aMessageType)
		{
			myMessagesSubscribedTo.erase(myMessagesSubscribedTo.begin() + messageTypeIndex);
			PostMaster::GetInstance().RemoveSubcriber(this, aMessageType);
			return;
		}
	}
}