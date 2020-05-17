// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
    GENERATED_BODY()
private:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    // Called every frame
    virtual void Tick(const float DeltaSeconds) override;


    // move barrel towards position where a shot would hit where crosshair intersects world
    void AimTowardsCrosshair();
    ATank* GetControlledTank() const;
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5;
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333;
};
