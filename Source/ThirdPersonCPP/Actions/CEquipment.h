#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actions/CActionData.h"
#include "CEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnequipmentDelegate);

class ACharacter;
class UCStateComponent;
class UCAttributeComponent;

UCLASS()
class THIRDPERSONCPP_API ACEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipment();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE const bool* IsEquipped() { return &bEquipped; }		// 실시간성 보장

	void SetData(const FEquipmentData& InData);
	void SetColor(const FLinearColor& InColor);

public:	
	UFUNCTION(BlueprintNativeEvent)
	void Equip();
	UFUNCTION(BlueprintNativeEvent)
	void Begin_Equip();
	UFUNCTION(BlueprintNativeEvent)
	void End_Equip();
	UFUNCTION(BlueprintNativeEvent)
	void Unequip();			// Unequip에는 몽타주가 들어가지 않을 예정이므로 노티파이 관련 함수 필요없음

protected:
	UPROPERTY(BlueprintReadOnly)
	ACharacter* OwnerCharacter;
	UPROPERTY(BlueprintReadOnly)
	UCStateComponent* StateComp;
	UPROPERTY(BlueprintReadOnly)
	UCAttributeComponent* AttributeComp;
	
public:
	UPROPERTY(BlueprintAssignable)
	FEquipmentDelegate OnEquipmentDelegate;
	UPROPERTY(BlueprintAssignable)
	FUnequipmentDelegate OnUnequipmentDelegate;

private:
	FEquipmentData Data;
	FLinearColor Color;

	bool bEquipped;
};
