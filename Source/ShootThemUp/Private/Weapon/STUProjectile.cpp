// Shoot Them Up. All Rights Reserved.


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"

// Sets default values
ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    SetRootComponent(CollisionComponent);
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
}

