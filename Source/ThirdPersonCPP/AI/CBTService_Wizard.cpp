#include "CBTService_Wizard.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"

UCBTService_Wizard::UCBTService_Wizard()
{
	NodeName = "Root_Wizard";
}

void UCBTService_Wizard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(AIC);

	ACEnemy_AI* EnemyPawn = Cast<ACEnemy_AI>(AIC->GetPawn());
	CheckNull(EnemyPawn);

	UCBehaviorComponent* BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(AIC);
	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(EnemyPawn);

	//Is Hitted
	if (StateComp->IsHittedMode())
	{
		BehaviorComp->SetHittedMode();
		return;
	}

	//Try Get PlayerKey from BB
	ACPlayer* Player = BehaviorComp->GetPlayerKey();

	//Player not detected
	if (Player == nullptr)
	{
		AIC->ClearFocus(EAIFocusPriority::Gameplay);
		BehaviorComp->SetWaitMode();
		return;
	}

	//Player detected
	AIC->SetFocus(Player);

	float Distance = EnemyPawn->GetDistanceTo(Player);

	if (Distance < AIC->GetBehaviorRange())
	{
		BehaviorComp->SetEscapeMode();
		return;
	}

	if (Distance < AIC->GetSightRadius())
	{
		BehaviorComp->SetActionMode();
	}
}