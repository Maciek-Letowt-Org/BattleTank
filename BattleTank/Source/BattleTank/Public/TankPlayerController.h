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
    bool GotLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
    bool GotSightRayHitLocation(FVector& OutHitLocation) const;

    // return result from ray cast in "look direction" from camera to World
    bool GotLookVectorHitLocation(FVector& LookDirection, FVector& OutHitLocation) const;

    UFUNCTION()
    void OnPossessedTankDeath();

    // ---------------- members / properties -------------------------------------------
    UTankAimingComponent* AimingComponent = nullptr;

    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5;
    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333;
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000;
    
    virtual void SetPawn(APawn* InPawn) override;
};
