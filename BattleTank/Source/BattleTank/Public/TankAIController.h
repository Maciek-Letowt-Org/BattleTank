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

protected:
    // how close to player in cm
    UPROPERTY(EditDefaultsOnly,Category = "Setup")
    float AcceptanceRadius = 8000.f;
private:
    UFUNCTION()
    void OnPossessedTankDeath();
    // ------- members & properties ---------------------------------
    virtual void SetPawn(APawn* InPawn) override;
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
};
