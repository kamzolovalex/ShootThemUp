// Shoot Them Up. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
    GENERATED_BODY()

    ASTUAIController();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUAIPerceptionComponent* STUAIPerceptionComponent;

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;
	
};
