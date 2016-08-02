
#pragma once

#include "GOAPAction.h"
#include "GOAPState.h"
#include "GOAPAIController.h"

class GOAPNode;

/**
*
*/
class GOAPER_API GOAPPlanner
{
public:
	static TArray<TSharedPtr<GOAPAction>> Plan(const EGOAPState aState,
		const bool aValue,
		TArray<TSharedPtr<GOAPAction>> aActions,
		TArray<TSharedPtr<GOAPState>> aCurrentState,
		AGOAPAIController& controller);
};
