#include "CBTTaskNode_Speed.h"
#include "Global.h"
#include "AIController.h"

UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIC = Cast<AAIController>(OwnerComp.GetOwner());
	CheckNullResult(AIC, EBTNodeResult::Type::Failed);

	APawn* Pawn = AIC->GetPawn();
	CheckNullResult(Pawn, EBTNodeResult::Type::Failed);

	UCAttributeComponent* AttributeComp = CHelpers::GetComponent<UCAttributeComponent>(Pawn);
	CheckNullResult(AttributeComp, EBTNodeResult::Type::Failed);

	AttributeComp->SetWalkSpeed(Type);
	return EBTNodeResult::Type::Succeeded;
}