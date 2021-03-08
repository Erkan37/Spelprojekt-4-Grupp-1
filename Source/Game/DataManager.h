#pragma once
#include "rapidjson/document.h"

struct Data
{
	enum class DataEnum
	{
		player = 0,
		enemy = 1,

		data_enum_size = 2
	};

	struct PlayerData
	{
		int myHealth;
		float myMoveSpeed;
	};
	struct Enemy
	{
		int myHealth;
		float myMoveSpeed;
	};

};


class DataManager
{
public:
	// Singleton Methods
	static DataManager& GetInstance()
	{
		static DataManager instance;
		return instance;
	}
	DataManager(DataManager& aDataManager) = delete;
	void operator=(const DataManager&) = delete;


	Data &GetDataStruct(const Data::DataEnum aDataEnum);


private:
	DataManager();

	Data myData;

};
