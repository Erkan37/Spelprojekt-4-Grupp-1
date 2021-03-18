#include "stdafx.h"
#include "PostMaster.hpp"

void PostMaster::AddSubcriber(Subscriber* aSubscriber, eMessageType aMessageType)
{
	if (mySubscribers.find(aMessageType) == mySubscribers.end())
	{
		mySubscribers.insert({aMessageType, std::vector<Subscriber*>()});
	}

	mySubscribers[aMessageType].push_back(aSubscriber);
}

void PostMaster::RemoveSubcriber(Subscriber* aSubscriber, eMessageType aMessageType)
{
	if (mySubscribers.find(aMessageType) != mySubscribers.end())
	{
		for (size_t subscriberIndex = 0; subscriberIndex < mySubscribers[aMessageType].size(); ++subscriberIndex)
		{
			if (mySubscribers[aMessageType][subscriberIndex] == aSubscriber)
			{
				mySubscribers[aMessageType].erase(mySubscribers[aMessageType].begin() + subscriberIndex);
				return;
			}
		}
	}
}

void PostMaster::ReceiveMessage(const Message& aMessageType)
{
	
}