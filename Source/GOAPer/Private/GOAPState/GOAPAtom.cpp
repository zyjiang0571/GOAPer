#include "GOAPer.h"
#include "GOAPAtom.h"
#include "GOAPerUtilLibrary.h"

FString GOAPAtom::ToString()
{
	FString result;

	switch (Key)
	{
	case EGOAPState::HasFood:
		result = TEXT("HasFood");
	case EGOAPState::IsHungry:
		result = TEXT("IsHungry");
	case EGOAPState::FoodAvailableState:
		result = TEXT("FoodAvailable");
	default:
		result = TEXT("Invalid");
	};

	if (Value)
	{
		result += TEXT("_1");
	}
	else 
	{
		result += TEXT("_0");
	}

	return result;
}

bool GOAPAtom::operator==(const GOAPAtom& aOther)
{
	return aOther.Key == Key && aOther.Value == Value;
}

GOAPAtom::GOAPAtom()
{
	
}

GOAPAtom::~GOAPAtom()
{

}