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

	void AddSubcriber(Subscriber* aSubscriber, eMessageType aMessageType);
	void RemoveSubcriber(Subscriber* aSubscriber, eMessageType aMessageType);

	void ReceiveMessage(const Message& aMessage);

private:
	PostMaster()
	{

	}

	std::map<eMessageType, std::vector<Subscriber*>> mySubscribers;

};

