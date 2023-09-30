// Shoot Them Up. All Rights Reserved.


#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/STUHealthBarWidget.h"
#include "Components/STUHealthComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("Weaponomponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASTUAICharacter::StaticClass();

    bUseControllerRotationYaw = false;

    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTUAICharacter::BeginPlay() 
{
    Super::BeginPlay();

    check(HealthWidgetComponent);
}

void ASTUAICharacter::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    UpdateHealthWidgetVisibility();
}
void ASTUAICharacter::UpdateHealthWidgetVisibility()
{
    
    if (!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;
    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());

    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}

void ASTUAICharacter::OnDeath() 
{
    Super::OnDeath();

    const auto STUController = Cast<AAIController>(Controller);
    if (STUController && STUController->BrainComponent)
    {
        STUController->BrainComponent->Cleanup();
    }
}

void ASTUAICharacter::HealthChanged(float Health, float HealthDelta)
{
    Super::HealthChanged(Health, HealthDelta);

    const auto HealthBarWidget = Cast<USTUHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!HealthBarWidget) return;
    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}