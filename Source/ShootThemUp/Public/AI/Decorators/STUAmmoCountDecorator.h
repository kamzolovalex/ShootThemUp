// Shoot Them Up. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUAmmoCountDecorator.generated.h"

class ASTUBaseWeapon;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUAmmoCountDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
    USTUAmmoCountDecorator();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
