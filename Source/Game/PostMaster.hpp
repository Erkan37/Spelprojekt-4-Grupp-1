#pragma once
#include "Message.hpp"
#include <map>
#include <vector>

class Subscriber;

class PostMaster
{
public:
	static PostMaster& GetInstance()
	{
		static PostMaster instance;
		return instance;
	}

	PostMaster(PostMaster& aPostMaster) = delete;
	void operator=(const PostMaster&) = delete;
	~PostMaster() = default;

	void AddSubcriber(Subscriber* aSubscriber, const eMessageType& aMessageType);
	void RemoveSubcriber(Subscriber* aSubscriber, const eMessageType& aMessageType);

	void ReceiveMessage(const Message& aMessage);
	void ReceiveMessage(const Message& aMessage, const bool aWillWait);

	void SendWaitingMessages();

private:
	PostMaster()
	{

	}

	std::map<eMessageType, std::vector<Subscriber*>> mySubscribers;
	std::vector<Message> myWaitingMessages;

};

