#include "CBehaviorComponent.h"

UCBehaviorComponent::UCBehaviorComponent()
{

}

void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCBehaviorComponent::SetBlackboardCom(UBlackboardComponent* InComp)
{
	BlackboardComp = InComp;
}

bool UCBehaviorComponent::IsWaitMode()
{
	return false;
}

bool UCBehaviorComponent::IsApproachMode()
{
	return false;
}

bool UCBehaviorComponent::IsActionMode()
{
	return false;
}

bool UCBehaviorComponent::IsPatrolMode()
{
	return false;
}

bool UCBehaviorComponent::IsHittedMode()
{
	return false;
}

bool UCBehaviorComponent::IsEscapeMode()
{
	return false;
}

void UCBehaviorComponent::SetWaitMode()
{
}

void UCBehaviorComponent::SetApproachMode()
{
}

void UCBehaviorComponent::SetActionMode()
{
}

void UCBehaviorComponent::SetPatrolMode()
{
}

void UCBehaviorComponent::SetHittedMode()
{
}

void UCBehaviorComponent::SetEscapeMode()
{
}

EBehaviorType UCBehaviorComponent::GetType()
{
	return EBehaviorType();
}

void UCBehaviorComponent::ChangeType(EBehaviorType InNewType)
{
}
