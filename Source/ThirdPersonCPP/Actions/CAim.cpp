#include "CAim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

UCAim::UCAim()
{
	CHelpers::GetAsset(&Curve, "/Game/Game/Curve_Aim");
}

void UCAim::BeginPlay(ACharacter* InOwnerCharacter)
{
	OwnerCharacter = InOwnerCharacter;
	
	SpringArmComp = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	CameraComp = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	FOnTimelineFloat OnProgressDelegate;
	OnProgressDelegate.BindUFunction(this, "OnProgress");
	Timeline.AddInterpFloat(Curve, OnProgressDelegate);
}

void UCAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);
}

void UCAim::On()
{
	CheckFalse(CanAim());
	CheckTrue(bZooming);

	bZooming = true;

	//->SpringArmComponent
	SpringArmComp->TargetArmLength = 100.f;
	SpringArmComp->SocketOffset = FVector(0, 30, 10);
	SpringArmComp->bEnableCameraLag = false;

	//->CameraComponent
	//CameraComp->FieldOfView = 45.f;
	Timeline.PlayFromStart();
}

void UCAim::Off()
{
	CheckFalse(CanAim());
	CheckFalse(bZooming);

	bZooming = false;

	//->SpringArmComponent
	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->SocketOffset = FVector(0, 0, 0);
	SpringArmComp->bEnableCameraLag = true;

	//->CameraComponent
	//CameraComp->FieldOfView = 90.f;
	Timeline.ReverseFromEnd();
}

void UCAim::OnProgress(float Output)
{
	CameraComp->FieldOfView = Output;
}
