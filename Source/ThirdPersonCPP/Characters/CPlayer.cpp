#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &SpringArmComp, "SpringArmComp", GetMesh());
	CHelpers::CreateSceneComponent(this, &CameraComp, "CameraComp", SpringArmComp);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.f, 0));

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Character/Mesh/SK_Mannequin");
	GetMesh()->SetSkeletalMesh(MeshAsset);

	TSubclassOf<UAnimInstance> AnimInstanceClass;
	CHelpers::GetClass<UAnimInstance>(&AnimInstanceClass, "/Game/Player/ABP_CPlayer");
	GetMesh()->SetAnimInstanceClass(AnimInstanceClass);
	
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 140.f));
	SpringArmComp->SetRelativeRotation(FRotator(0, 90.f, 0));
	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", ACPlayer::OnTurn);
	PlayerInputComponent->BindAxis("LookUp", ACPlayer::OnLookUp);
}

void ACPlayer::OnMoveForward(float AixsValue)
{
}

void ACPlayer::OnMoveRight(float AixsValue)
{
}

void ACPlayer::OnTurn(float AixsValue)
{
}

void ACPlayer::OnLookUp(float AixsValue)
{
}

