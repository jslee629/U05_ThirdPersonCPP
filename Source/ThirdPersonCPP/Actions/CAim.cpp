#include "CAim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CHUD.h"

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

	//Load HUD From GameMode
	//UGameplayStatics::GetGameMode(OwnerCharacter->GetWorld())->HUDClass->GetDefaultObject();

	//Load HUD From PlayerController
	APlayerController* PC = OwnerCharacter->GetWorld()->GetFirstPlayerController();
	CheckNull(PC);

	HUD = PC->GetHUD<ACHUD>();
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

	HUD->VisibleAim();

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

	HUD->InvisibleAim();

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
