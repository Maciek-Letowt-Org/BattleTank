// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TankPlayerUI.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankPlayerUI : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
    class UCanvasPanel* Panel;
	UPROPERTY(meta = (BindWidget))
    class UImage* AimPoint;
	// UPROPERTY(meta = (BindWidget))
 //    class UTextBlock* AmmoText;
};
