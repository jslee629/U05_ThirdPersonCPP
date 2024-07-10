#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

class ACEnemy_AI;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UCBehaviorComponent;

UCLASS()
class THIRDPERSONCPP_API ACAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UCBehaviorComponent* BehaviorComp;
	UPROPERTY(VisibleDefaultsOnly)
	UAIPerceptionComponent* PerceptionComp;

private:
	ACEnemy_AI* OwnerEnemy;
	UAISenseConfig_Sight* Sight;
};
