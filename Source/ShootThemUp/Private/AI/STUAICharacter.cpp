// Shoot Them Up. All Rights Reserved.


#include "AI/STUAICharacter.h"

ASTUAICharacter::ASTUAICharacter() 
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTUAICharacter::StaticClass();
}