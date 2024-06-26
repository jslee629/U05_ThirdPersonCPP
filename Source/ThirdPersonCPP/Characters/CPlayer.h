#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Interfaces/CCharacterInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCAttributeComponent;
class UCOptionComponent;
class UCStateComponent;
class UCMontagesComponent;
class UCActionComponent;
class UMaterialInstanceDynamic;

UCLASS()
class THIRDPERSONCPP_API ACPlayer : public ACharacter, public ICCharacterInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float AixsValue);
	void OnMoveRight(float AixsValue);
	void OnTurn(float AixsValue);
	void OnLookUp(float AixsValue);
	void OnZoom(float AixsValue);
	void OnWalk();
	void OffWalk();
	void OnEvade();
	void OnFist();
	void OnOneHand();
	void OnTwoHand();
	void OnMagicBall();
	
private:
	void Begin_Roll();
	void Begin_Backstep();

public:
	void End_Roll();
	void End_Backstep();

private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

protected:
	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCOptionComponent* OptionComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCMontagesComponent* MontagesComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;

public:
	// Inherited via ICCharacterInterface
	virtual void ChangeBodyColor(FLinearColor InColor);

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;
};
