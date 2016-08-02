#pragma once
#include "GOAPGoal.h"
#include "IsHungryState.h"

class GOAPGoalFactory
{
public:
	static TSharedPtr<GOAPGoal> Create(EGOAPGoal aGoal);
};


TSharedPtr<GOAPGoal> GOAPGoalFactory::Create(EGOAPGoal aGoal)
{
	TSharedPtr<GOAPGoal> _goal = MakeShareable<GOAPGoal>(new GOAPGoal());

	switch (aGoal)
	{
	case EGOAPGoal::BeNourished:
		_goal->TargetState.Add(MakeShareable<GOAPAtom>(new GOAPAtom(EGOAPState::IsHungry, false)));
		return _goal;
	case EGOAPGoal::MakeFoodAvailable:
		_goal->TargetState.Add(MakeShareable<GOAPAtom>(new GOAPAtom(EGOAPState::FoodAvailableState,true)));
		return _goal;
	default:
		return nullptr;
	}
}