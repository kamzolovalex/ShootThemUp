// Shoot Them Up. All Rights Reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
//#include "TimerManager.h"
//#include "Engine/World.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);

	AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}

    
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead()) return;
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);

	if (IsDead())
    {
        OnDeath.Broadcast();
	}
    
    if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealHandle, this, &USTUHealthComponent::Heal, HealUpdateTime, true, HealDelay);
    }
}

void USTUHealthComponent::Heal()
{
    if (Health < MaxHealth)
    {
        UE_LOG(LogHealthComponent, Display, TEXT("Character starded healing: +%f"), HealModifier);
        Health = FMath::Clamp(Health + HealModifier, HealModifier, MaxHealth);
        OnHealthChanged.Broadcast(Health);
    }
    else
    {
        GetWorld()->GetTimerManager().ClearTimer(HealHandle);
        return;
    }
}
