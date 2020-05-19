// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
    GENERATED_BODY()
private:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(const float DeltaSeconds) override;
    
    ATank* GetControlledTank() const;
    ATank* GetPlayerTank() const;
    void AimTowardsPlayer() const;
};
