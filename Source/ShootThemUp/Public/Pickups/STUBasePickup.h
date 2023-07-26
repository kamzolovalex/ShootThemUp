// Shoot Them Up. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;

	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FTimerHandle RespawnTimerHandle;

public:	
	virtual void Tick(float DeltaTime) override;
    bool CouldBeTaken();

private:

	float RotationYaw = 0.0f;

    virtual bool GivePickupTo(APawn* PlayerPawn);

    void PickUpWasTaken();
    void PickupRespawn();
    void GenerateRotaionYaw();


};
