#include "CActionComponent.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "GameFramework/Character.h"

UCActionComponent::UCActionComponent()
{

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (DataAssets[i])
		{
			DataAssets[i]->BeginPlay(OwnerCharacter);
		}
	}
}

void UCActionComponent::SetUnarmedMode()
{
	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void UCActionComponent::SetMagicBallMode()
{
	SetMode(EActionType::MagicBall);
}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetWhirlwindMode()
{
	SetMode(EActionType::Whirlwind);
}

void UCActionComponent::SetMode(EActionType InNewType)
{
	if (Type == InNewType)
	{
		SetUnarmedMode();
		return;
	}

	ChangeType(InNewType);
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
