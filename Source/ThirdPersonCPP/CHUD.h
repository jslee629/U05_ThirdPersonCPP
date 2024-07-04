#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

class UCStateComponent;

UCLASS()
class THIRDPERSONCPP_API ACHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACHUD();
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

public:
	void VisibleAim();
	void InvisibleAim();

private:
	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrossHairTexture;

	bool bVisibleAim;

	UEnum* StateTypeAsUEnum;
	UCStateComponent* StateComp;
};
