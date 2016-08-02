#include "GOAPer.h"
#include "GOAPAIController.h"
#include "HasFoodState.h"
#include "EatAction.h"
#include "IsHungryState.h"

EatAction::EatAction()
{
	// Must have food
	PreConditions.Add(MakeShareable<GOAPAtom>(new GOAPAtom(EGOAPState::HasFood, true)));
	// Makes us not hungry!
	Effects.Add(MakeShareable<GOAPAtom>(new GOAPAtom(EGOAPState::IsHungry, false)));
}

bool EatAction::Execute(AGOAPAIController& controller)
{
	if ((&controller)->character->Stat_HasFood)
	{
		(&controller)->character->Stat_HasFood = false;
		(&controller)->character->Stat_Nutrition_Value += 10;
		return true;
	}

	return false;
}

FString EatAction::GetTextDescription()
{
	return TEXT("Eat");
}

