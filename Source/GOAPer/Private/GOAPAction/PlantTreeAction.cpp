#include "GOAPer.h"
#include "GOAPAIController.h"
#include "GameFramework/Actor.h"
#include "PlantTreeAction.h"
#include "IsFoodAvailableState.h"
#include "Kismet/KismetMathLibrary.h"

PlantTreeAction::PlantTreeAction()
{
	InteractionRange = 200.0f;

	hasMoved = false;

	// Make food!
	Effects.Add(MakeShareable<GOAPAtom>(new GOAPAtom(EGOAPState::FoodAvailableState, true)));

}

bool PlantTreeAction::Execute(AGOAPAIController& controller)
{
	// Check if the desired effects are already valid, if so, we're done
	if (AreEffectsSatisfied(controller))
	{
		return true;
	}

	if (!hasMoved)
	{
		// First pick a random point in front of the agent to move to
		FVector randomPoint = UKismetMathLibrary::RandomUnitVectorInCone((&controller)->GetActorForwardVector(), 45.0f) * FMath::FRandRange(500.0, 1000.0f);

		(&controller)->SetMoveToStateWithTarget((&controller)->character->GetActorLocation() + randomPoint);

		hasMoved = true;
	}
	// Otherwise, we're where we want to be
	else
	{
		AResourceActor* resource;
		UWorld* world = (&controller)->GetWorld();

		resource = world->SpawnActor<AResourceActor>(AResourceActor::StaticClass(), (&controller)->character->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f), FRotator(0.0f));
		resource->ResourceType = EResourceType::Food;
		return true;
	}

	return false;
}

FString PlantTreeAction::GetTextDescription()
{
	return TEXT("Create Food");
}

