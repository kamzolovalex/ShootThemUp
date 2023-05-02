// Shoot Them Up. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
    bool IsDead() const { return Health <= 0.0f; }

	FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

	FTimerHandle HealHandle;

    UFUNCTION()
    void Heal();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	float HealUpdateTime = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    float HealDelay = 3.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    float HealModifier = 1.f;

private:
    float Health = 0.0f;

	UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);



	
};
