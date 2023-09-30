// Shoot Them Up. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter
{
    GENERATED_BODY()

    virtual void Tick(float DeltaTime) override;

public:
    ASTUAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    float HealthVisibilityDistance = 1000.0f;

    virtual void BeginPlay() override;
    virtual void OnDeath() override;
    virtual void HealthChanged(float Health, float HealthDelta) override;

    private:
    void UpdateHealthWidgetVisibility();
};
