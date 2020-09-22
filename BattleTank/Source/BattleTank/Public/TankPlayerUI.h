// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "TankPlayerUI.generated.h"

/**
 * class to control the HUD
 */
UCLASS()
class BATTLETANK_API UTankPlayerUI final : public UUserWidget
{
    GENERATED_BODY()
    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel* Panel;
    UPROPERTY(meta = (BindWidget))
    class UImage* AimPoint;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* AmmoText;
};
