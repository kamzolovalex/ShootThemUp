// Shoot Them Up. All Rights Reserved.


#include "AI/Decorators/STUAmmoCountDecorator.h"
#include "Components/STUWeaponComponent.h"
#include "Components/STUHealthComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "AIController.h"
#include "STUUtils.h"

USTUAmmoCountDecorator::USTUAmmoCountDecorator() 
{
    NodeName = "Need Ammo";
}

bool USTUAmmoCountDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->NeedAmmo(WeaponClass);
}