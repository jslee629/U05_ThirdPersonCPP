#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCAttributeComponent;
class UCOptionComponent;

UCLASS()
class THIRDPERSONCPP_API ACPlayer : public ACharacter
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

protected:
	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(BlueprintReadOnly, Instanced, VisibleDefaultsOnly, Category = "Components")
	UCOptionComponent* OptionComp;
};
