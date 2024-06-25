#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	CheckNull(TryGetPawnOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(TryGetPawnOwner());
	CheckNull(ActionComp);

	ActionComp->OnActionTypeChanged.AddDynamic(this, &UCAnimInstance::OnActionTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	ACharacter* Character =  Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(Character);

	Speed = Character->GetVelocity().Size2D();
	Direction = CalculateDirection(Character->GetVelocity(), Character->GetControlRotation());
}

void UCAnimInstance::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	ActionType = InNewType;
}