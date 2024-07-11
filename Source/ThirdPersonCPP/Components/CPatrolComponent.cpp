#include "CPatrolComponent.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "AI/CPatrolPath.h"

UCPatrolComponent::UCPatrolComponent()
{
}

void UCPatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

bool UCPatrolComponent::GetMoveTo(FVector& OutLocation)
{
	CheckFalseResult(IsPathValid(), false);

	OutLocation = PatrolPath->GetSplineComp()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
	return true;
}

void UCPatrolComponent::UpdateNextIndex()
{
	CheckNull(PatrolPath);

	int32 Count = PatrolPath->GetSplineComp()->GetNumberOfSplinePoints();

	//reverse
	if (bReverse)
	{
		if (Index > 0)
		{
			Index--;
			return;
		}

		if (PatrolPath->GetSplineComp()->IsClosedLoop())
		{
			Index = Count - 1;
			return;
		}

		Index = 1;
		bReverse = false;
		return;
	}

	//forward
	if (Index < Count - 1)
	{
		Index++;
		return;
	}

	if (PatrolPath->GetSplineComp()->IsClosedLoop())
	{
		Index = 0;
		return;
	}

	Index = Count - 2;
	bReverse = true;
}

