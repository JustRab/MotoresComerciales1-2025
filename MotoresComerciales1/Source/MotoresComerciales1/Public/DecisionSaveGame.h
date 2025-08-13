#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DecisionSaveGame.generated.h"

UCLASS()
class UDecisionSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<FName, int32> Decisions;
};
