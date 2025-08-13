#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueTypes.generated.h"

USTRUCT(BlueprintType)
struct FDialogueCondition
{
	GENERATED_BODY()

	// Example: Key="SawPoster", RequiredValue=1 means "only show if SawPoster == 1"
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Key = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RequiredValue = 1;

	// If true, condition is inverted (e.g., show if Key != RequiredValue)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bInverted = false;
};

USTRUCT(BlueprintType)
struct FDialogueChoice
{
	GENERATED_BODY()

	// What the button shows
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Text;

	// Next node to go after picking this choice. None = end dialogue
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName NextNodeId = NAME_None;

	// Optional: set a flag/decision when picked (e.g., Key="TrustPolice", Value=1)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SetFlag = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SetValue = 1;

	// Optional: conditions for this choice to appear
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDialogueCondition> Conditions;
};

USTRUCT(BlueprintType)
struct FDialogueNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Id = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = "true"))
	FText Line;

	// If these aren't met, the node is skipped (engine will try to find next valid via NextNodeId)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDialogueCondition> Conditions;

	// Choices. If empty and AutoNextId is None => end dialogue
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDialogueChoice> Choices;

	// Optional auto advance
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAutoAdvance = false;

	// If auto advance or single linear flow
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName AutoNextId = NAME_None;
};

UCLASS(BlueprintType)
class UDialogueGraphData : public UDataAsset
{
	GENERATED_BODY()
public:
	// Entry point node
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StartNode = NAME_None;

	// Your nodes live here; use unique Id for each one
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, FDialogueNode> Nodes;
};
