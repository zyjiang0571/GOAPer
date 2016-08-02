#pragma once
#include "GOAPer.h"

UENUM()
enum class EGOAPState : uint8
{
	HasFood			UMETA(DisplayName = "Has Food"),
	IsHungry		UMETA(DisplayName = "Is Hungry"),
	FoodAvailableState UMETA(DisplayName = "Food Available")
};

class GOAPAtom
{
public:
	GOAPAtom(EGOAPState eKey, bool bValue) : Key{ eKey }, Value{ bValue } {};
	GOAPAtom();
	~GOAPAtom();
	EGOAPState Key;
	bool Value;
	FString ToString();
	bool operator==(const GOAPAtom& aOther);
};