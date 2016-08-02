
#pragma once
#include "GOAPAction.h"
#include "GatherFoodAction.h"
#include "EatAction.h"
#include "PlantTreeAction.h"


class GOAPActionFactory
{
public:
	static TSharedPtr<GOAPAction> Create(EGOAPAction aAction);
};


TSharedPtr<GOAPAction> GOAPActionFactory::Create(EGOAPAction aAction)
{
	switch (aAction)
	{
	case EGOAPAction::GatherFood:
		return MakeShareable<GOAPAction>(new GatherFoodAction());
	case EGOAPAction::Eat:
		return MakeShareable<GOAPAction>(new EatAction());
	case EGOAPAction::CreateFood:
		return MakeShareable<GOAPAction>(new PlantTreeAction());
	default:
		return nullptr;
	}
}