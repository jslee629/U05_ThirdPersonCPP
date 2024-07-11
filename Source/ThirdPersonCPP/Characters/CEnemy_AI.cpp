#include "CEnemy_AI.h"
#include "Global.h"
#include "Components/CPatrolComponent.h"

ACEnemy_AI::ACEnemy_AI()
{
	TeamId = 1;
	
	CHelpers::CreateActorComponent<UCPatrolComponent>(this, &PatrolComp, "PatrolComp");
}