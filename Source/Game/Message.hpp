#pragma once
#include "MessageTypes.hpp"
#include <string>
#include <variant>

struct Message
{
	Message(const eMessageType& aMessageType, const int& aIntData)
	{
		myMessageType = aMessageType;
		myData = aIntData;
	}

	Message(const eMessageType& aMessageType, const float& aFloatData)
	{
		myMessageType = aMessageType;
		myData = aFloatData;
	}

	Message(const eMessageType& aMessageType, const std::string& aStringData)
	{
		myMessageType = aMessageType;
		myData = aStringData;
	}

	~Message() = default;

	eMessageType myMessageType;

	std::variant<int, float, std::string> myData;
};

