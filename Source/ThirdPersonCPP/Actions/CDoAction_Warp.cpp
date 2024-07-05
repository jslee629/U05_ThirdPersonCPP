#include "CDoAction_Warp.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstance.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"
#include "CAttachment.h"

void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();

	//OwnerCharacter�� Owner�� ����ϰ� �ִ� ��� ���͸� ��ȯ
	for (const auto& Child : OwnerCharacter->Children)
	{
		if (Child->IsA<ACAttachment>() && Child->GetActorLabel().Contains("Warp"))
		{
			PreviewMeshComp = CHelpers::GetComponent<USkeletalMeshComponent>(Child);
			break;
		}
	}
}

void ACDoAction_Warp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PreviewMeshComp->SetVisibility(false);

	CheckFalse(*bEquipped);			// �ּҸ� ���������� �տ� * ������ ���̴°� ����

	FVector CurLoc;
	FRotator CurRot;

	if (GetCursorLocationAndRotation(CurLoc, CurRot))
	{
		PreviewMeshComp->SetVisibility(true);
		PreviewMeshComp->SetWorldLocation(CurLoc);
	}
}

void ACDoAction_Warp::DoAction()
{
	Super::DoAction();

	CheckFalse(StateComp->IsIdleMode());

	FRotator Temp;
	CheckFalse(GetCursorLocationAndRotation(Location, Temp));

	StateComp->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();

	PreviewMeshComp->SetVectorParameterValueOnMaterials("Emissive", FVector(0, 20, 0));
}

void ACDoAction_Warp::Begin_DoAction()
{
	Super::Begin_DoAction();

	FTransform Transform = Datas[0].EffectTransform;
	Transform.AddToTranslation(OwnerCharacter->GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Datas[0].Effect, Transform);

	PreviewMeshComp->SetVectorParameterValueOnMaterials("Emissive", FVector(20, 0, 0));
}

void ACDoAction_Warp::End_DoAction()
{
	Super::End_DoAction();

	Location.Z += OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	OwnerCharacter->SetActorLocation(Location);

	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}

bool ACDoAction_Warp::GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotation)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);

	FHitResult Hit;
	if (PC->GetHitResultUnderCursorForObjects(ObjectTypes, true, Hit))
	{
		OutLocation = Hit.Location;
		OutRotation = Hit.ImpactNormal.Rotation();

		return true;
	}

	return false;
}
