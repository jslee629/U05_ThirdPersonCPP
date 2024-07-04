#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_MagicBall.generated.h"

class UCAim;

UCLASS()
class THIRDPERSONCPP_API ACDoAction_MagicBall : public ACDoAction
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnProjectileBeginOverlap(FHitResult InHitResult);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void DoAction() override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction() override;
	virtual void Begin_SubAction() override;
	virtual void End_SubAction() override;

private:
	UPROPERTY()
	UCAim* Aim;
};
