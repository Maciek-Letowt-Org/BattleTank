// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"
/**
 * AI NPC - Depends on movement component via pathfinding system. Called when the game starts or when spawned
 */
UCLASS()
class BATTLETANK_API ATankAIController final : public AAIController
{
    GENERATED_BODY()
private:
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
    // ------- members & properties ---------------------------------
    // how close to player in cm
    UPROPERTY(EditDefaultsOnly)
    float AcceptanceRadius = 3000.f;
};
