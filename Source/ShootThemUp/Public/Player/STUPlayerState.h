// Shoot Them Up. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    void SetTeamID(int32 ID) { TeamID = ID; }
    int32 GetTeamID() const { return TeamID; }

	void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }
    FLinearColor GetTeamColor() const { return TeamColor; }

	void AddKillsNum() { ++KillsNum; }
    int32 GetKillsNum() const { return KillsNum; }

	void AddDeathNum() { ++DeathNum; }
    int32 GetDeathNum() { return DeathNum; }

	void LogInfo();

protected:
	int32 TeamID;
    FLinearColor TeamColor;
	
	int32 KillsNum = 0;
    int32 DeathNum = 0;
};
