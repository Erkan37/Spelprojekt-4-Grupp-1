#include "stdafx.h"
#include "DataManager.h"


Data& DataManager::GetDataStruct(const Data::DataEnum aDataEnum)
{
	switch (aDataEnum)
	{
	case Data::DataEnum::enemy:
	{
		return myData;
	}
	break;


	default:
		break;
	}
}
