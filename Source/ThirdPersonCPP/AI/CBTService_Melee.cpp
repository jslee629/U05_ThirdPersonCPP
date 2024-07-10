#include "CBTService_Melee.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"

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

	//Is Hitted
	if (StateComp->IsHittedMode())
	{
		BehaviorComp->SetHittedMode();
		return;
	}

	//Try Get PlayerKey from BB
	ACPlayer* Player = BehaviorComp->GetPlayerKey();

	//player not detected
	if (Player == nullptr)
	{
		BehaviorComp->SetWaitMode();
		return;
	}

	//player detected
	//TODO: 감지 범위를 AIController를 통해서 가져오고 공격 범위를 공개 변수로
}
