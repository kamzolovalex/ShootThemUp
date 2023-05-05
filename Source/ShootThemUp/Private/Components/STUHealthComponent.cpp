// Shoot Them Up. All Rights Reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/World.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;

    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealHandle);

	if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal && !IsDead())
    {
        GetWorld()->GetTimerManager().SetTimer(HealHandle, this, &USTUHealthComponent::Heal, HealUpdateTime, true, HealDelay);
    }
}

void USTUHealthComponent::Heal()
{
    UE_LOG(LogHealthComponent, Display, TEXT("Character starded healing: +%f"), HealModifier);
    SetHealth(Health + HealModifier);

    if (FMath::IsNearlyEqual(Health, MaxHealth))
    {
        GetWorld()->GetTimerManager().ClearTimer(HealHandle);
    }
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}