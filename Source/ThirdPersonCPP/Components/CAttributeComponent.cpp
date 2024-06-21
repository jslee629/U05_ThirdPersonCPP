#include "CAttributeComponent.h"
#include "Global.h"

UCAttributeComponent::UCAttributeComponent()
{
	// initialize member variables
	WalkSpeeds[(int32)EWalkSpeedType::Sneak] = 200;
	WalkSpeeds[(int32)EWalkSpeedType::Walk] = 400;
	WalkSpeeds[(int32)EWalkSpeedType::Sprint] = 600;
	MaxHealth = 100.f;
	bCanMove = true;
}


void UCAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	CurHealth = MaxHealth;
	
}

void UCAttributeComponent::IncreaseHealth(float InAmount)
{
	CurHealth += InAmount;
	CurHealth = FMath::Clamp(CurHealth, 0.f, MaxHealth);
}

void UCAttributeComponent::DecreaseHealth(float InAmount)
{
	CurHealth -= InAmount;
	CurHealth = FMath::Clamp(CurHealth, 0.f, MaxHealth);
}

void UCAttributeComponent::SetMove()
{
	bCanMove = true;
}

void UCAttributeComponent::SetStop()
{
	bCanMove = false;
}



