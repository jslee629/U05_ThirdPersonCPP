#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CCharacterInterface.h"
#include "Components/CStateComponent.h"
#include "Components/TimelineComponent.h"
#include "CEnemy.generated.h"

class UCAttributeComponent;
class UCMontagesComponent;
class UCActionComponent;
class UMaterialInstanceDynamic;
class UWidgetComponent;
class AController;
class UCurveFloat;

UCLASS()
class THIRDPERSONCPP_API ACEnemy : public ACharacter, public ICCharacterInterface
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:	
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCMontagesComponent* MontagesComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* NameWidgetComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* HealthWidgetComp;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
	float LaunchValue;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Curve")
	UCurveFloat* DissolveCurve;

public:
	// Inherited via ICCharacterInterface
	virtual void ChangeBodyColor(FLinearColor InColor) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	void Hitted();
	void Dead();

	UFUNCTION()
	void RestoreLogoColor();

	UFUNCTION()
	void StartDissolve(float Output);

	UFUNCTION()
	void EndDissolve();

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	UPROPERTY(VisibleInstanceOnly)
	UMaterialInstanceDynamic* DissolveMaterial;		//c++에서 알아서 할당 해제를 하지 않도록 해줌

	AController* DamageInstigator;
	float DamageValue;

	FTimeline DissolveTime;
};
