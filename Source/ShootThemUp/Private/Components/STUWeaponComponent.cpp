// Shoot Them Up. All Rights Reserved.


#include "Components/STUWeaponComponent.h"
#include "Animations/STUWquipFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
    InitAnimations(); 
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    for (auto WeaponClass : WeaponClasses)
    {
        auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
        if (!Weapon) continue;

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) 
{
    if (!Weapon || !SceneComponent) return;

    FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRule, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex) 
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire() 
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void USTUWeaponComponent::NextWeapon() 
{
    if (!CanEquip()) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) 
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    Character->PlayAnimMontage(Animation);
}

void USTUWeaponComponent::InitAnimations() 
{
    if (!EquipAnimMontage) return;
    const auto NotifyEvents = EquipAnimMontage->Notifies;
    for (auto NotifyEvent : NotifyEvents)
    {
        auto EquipFinishedNotify = Cast<USTUWquipFinishedAnimNotify>(NotifyEvent.Notify);
        if (EquipFinishedNotify)
        {
            EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
            break;
        }
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent) return;
    
    EquipAnimInProgress = false;
}

bool USTUWeaponComponent::CanFire() const 
{
    return CurrentWeapon && !EquipAnimInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress;
}