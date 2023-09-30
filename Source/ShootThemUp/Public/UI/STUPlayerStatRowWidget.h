// Shoot Them Up. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    void SetPlayerName(const FText& Text);
    void SetKills(const FText& Text);
    void SetDeaths(const FText& Text);
    void SetTeam(const FText& Text);
    void SetPlayerIndicatorVisibility(bool Visible);
    void SetTeamColor(const FLinearColor& Color);

protected:
    UPROPERTY(meta = (bindWidget));
    UTextBlock* PlayerNameTextBlock;
	
    UPROPERTY(meta = (bindWidget));
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta = (bindWidget));
    UTextBlock* DeathsTextBlock;

    UPROPERTY(meta = (bindWidget));
    UTextBlock* TeamTextBlock;

    UPROPERTY(meta = (bindWidget));
    UImage* PlayerIndicatorImage;

    UPROPERTY(meta = (bindWidget));
    UImage* TeamImage;
};
