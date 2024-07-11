#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"

class UBehaviorTree;
class UCPatrolComponent;

UCLASS()
class THIRDPERSONCPP_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()
	
public:
	ACEnemy_AI();

public:
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamId() { return TeamId; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	uint8 TeamId;
	UPROPERTY(VisibleDefaultsOnly)
	UCPatrolComponent* PatrolComp;
};
