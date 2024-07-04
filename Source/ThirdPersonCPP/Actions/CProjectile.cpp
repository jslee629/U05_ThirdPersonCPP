#include "CProjectile.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACProjectile::ACProjectile()
{
	//Create Scene Component
	CHelpers::CreateSceneComponent(this, &SphereComp, "SphereComp");
	CHelpers::CreateSceneComponent(this, &ParticleComp, "ParticleComp", SphereComp);

	//Create Actor Component
	CHelpers::CreateActorComponent(this, &ProjectileComp, "ProjectileComp");

	//->Projectile Movement Component
	InitialLifeSpan = 3.f;
	ProjectileComp->InitialSpeed = 4000.f;
	ProjectileComp->MaxSpeed = 8000.f;
	ProjectileComp->ProjectileGravityScale = 0.f;
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile::OnComponentBeginOverlap);
}

void ACProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PrintLine();
	CheckTrue(OtherActor == GetOwner());


	if (OnProjectileBeginOverlap.IsBound())
	{
		OnProjectileBeginOverlap.Broadcast(SweepResult);
	}

	Destroy();
}


