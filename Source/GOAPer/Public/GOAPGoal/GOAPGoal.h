#pragma once
#include "GOAPer.h"
#include "GOAPAtom.h"

class AGOAPAIController;

UENUM()
enum class EGOAPGoal : uint8
{
	BeNourished		UMETA(DisplayName = "Be Nourished"),
	MakeFoodAvailable UMETA(DisplayName = "Make Food Available")
};

class GOAPGoal
{
public:
	TArray<TSharedPtr<GOAPAtom>> TargetState;

	bool IsTargetStateSatisfied(AGOAPAIController& controller);
};
