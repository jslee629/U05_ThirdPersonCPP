#include "CActionComponent.h"
#include "Global.h"

UCActionComponent::UCActionComponent()
{

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCActionComponent::SetUnarmedMode()
{
}

void UCActionComponent::SetFistMode()
{
}

void UCActionComponent::SetOneHandMode()
{
}

void UCActionComponent::SetTwoHandMode()
{
}

void UCActionComponent::SetMagicBallMode()
{
}

void UCActionComponent::SetWarpMode()
{
}

void UCActionComponent::SetWhirlwindMode()
{
}

void UCActionComponent::SetMode()
{
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType Prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
	{

		OnActionTypeChanged.Broadcast(Prev, InNewType);
	}
}
