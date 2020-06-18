// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"
class ATank;
/**
 * AI NPC
 */
UCLASS()
class BATTLETANK_API ATankAIController final : public AAIController
{
    GENERATED_BODY()
private:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
};
