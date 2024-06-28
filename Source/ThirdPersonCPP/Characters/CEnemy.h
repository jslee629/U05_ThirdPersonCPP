#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CCharacterInterface.h"
#include "Components/CStateComponent.h"
#include "CEnemy.generated.h"

class UCAttributeComponent;
class UCMontagesComponent;
class UCActionComponent;
class UMaterialInstanceDynamic;
class UWidgetComponent;
class AController;

UCLASS()
class THIRDPERSONCPP_API ACEnemy : public ACharacter, public ICCharacterInterface
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	virtual void BeginPlay() override;

protected:	
	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCMontagesComponent* MontagesComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* NameWidgetComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* HealthWidgetComp;

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

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	AController* DamageInstigator;
};
