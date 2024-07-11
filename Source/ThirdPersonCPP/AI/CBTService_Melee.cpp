#include "CBTService_Melee.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CPatrolComponent.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Root_Melee";
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetOwner());
	CheckNull(AIC);

	ACEnemy_AI* EnemyPawn = Cast<ACEnemy_AI>(AIC->GetPawn());
	CheckNull(EnemyPawn);

	UCBehaviorComponent* BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(AIC);
	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(EnemyPawn);
	UCPatrolComponent* PatrolComp = CHelpers::GetComponent<UCPatrolComponent>(EnemyPawn);

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
		if (PatrolComp->IsPathValid())
		{
			BehaviorComp->SetPatrolMode();
			return;
		}
		else
		{
			BehaviorComp->SetWaitMode();
			return;
		}
	}

	//Player detected
	float Distance = EnemyPawn->GetDistanceTo(Player);

	if (Distance < AIC->GetBehaviorRange())
	{
		BehaviorComp->SetActionMode();
		return;
	}

	if (Distance < AIC->GetSightRadius())
	{
		BehaviorComp->SetApproachMode();
	}
}
