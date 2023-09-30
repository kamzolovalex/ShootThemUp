// Shoot Them Up. All Rights Reserved.


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GamePlayStatics.h"


// Sets default values
ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("STUWeaponFXComponent");


}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);
    
    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

void ASTUProjectile::OnProjectileHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld()) return;

    MovementComponent->StopMovementImmediately();

    UGameplayStatics::ApplyRadialDamage(
        GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, DamageType, {GetOwner()}, this, GetController(), DoFullDamage);
    
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ProjectileExplosionSound, GetActorLocation());
    WeaponFXComponent->PlayImpactFX(Hit);
    Destroy();
}

AController* ASTUProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}