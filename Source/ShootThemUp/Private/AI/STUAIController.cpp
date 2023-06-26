// Shoot Them Up. All Rights Reserved.


#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController() 
{
    STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("PerceptionComponent");
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<ASTUAICharacter>(InPawn);

    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }

}

void ASTUAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    //const auto AimActor = STUAIPerceptionComponent->GetClosestEnemy();
    //SetFocus(AimActor);
    UE_LOG(LogTemp, Display, TEXT("Aim Actor: %s"), *STUAIPerceptionComponent->GetClosestEnemy()->GetName());
}