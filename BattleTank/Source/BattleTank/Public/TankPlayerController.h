// copyright Maciek Letowt 2020
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
class UTankAimingComponent; // FD
/**
 *  Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController final : public APlayerController
{
    GENERATED_BODY()
protected:
    UFUNCTION(BlueprintImplementableEvent, Category="Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;

    // move barrel towards position where a shot would hit where crosshair intersects world
    void AimTowardsCrosshair() const;
    bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
    bool GetLookVectorHitLocation(FVector& LookFrom, FVector& OutHitLocation) const;
    
    // ---------------- members / properties -------------------------------------------
    UTankAimingComponent* AimingComponent = nullptr;

    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5;
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333;
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000;
};
