#include "CBTTaskNode_Action.h"
#include "Global.h"
#include "AIController.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CBehaviorComponent.h"
#include "Characters/CPlayer.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
	bNotifyTick = true;

	NodeName = "Action";
	Delay = 2.f;
}

EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIC = Cast<AAIController>(OwnerComp.GetOwner());
	CheckNullResult(AIC, EBTNodeResult::Failed);

	APawn* Pawn = AIC->GetPawn();
	CheckNullResult(Pawn, EBTNodeResult::Failed);

	UCBehaviorComponent* BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(AIC);
	CheckNullResult(BehaviorComp, EBTNodeResult::Failed);

	AIC->SetFocus(BehaviorComp->GetPlayerKey());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(Pawn);
	CheckNullResult(ActionComp, EBTNodeResult::Failed);

	ActionComp->DoAction();

	ElapsedTime = 0.f;

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = Cast<AAIController>(OwnerComp.GetOwner());
	CheckNull(AIC);

	APawn* Pawn = AIC->GetPawn();
	CheckNull(Pawn);

	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(Pawn);
	CheckNull(StateComp);

	ElapsedTime += DeltaSeconds;

	if (StateComp->IsIdleMode() && ElapsedTime > Delay)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
