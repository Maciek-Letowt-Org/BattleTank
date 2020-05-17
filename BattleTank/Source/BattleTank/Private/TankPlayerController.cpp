// copyright Maciek Letowt 2020


#include "TankPlayerController.h"

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    // logs computerNameHexWord
    UE_LOG(LogTemp, Warning, TEXT("tank player controller pawn %s"), *GetPawn()->GetHumanReadableName());;
    ATank* TankPtr = GetControlledTank();
    if (TankPtr)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank player controller tank %s"), *TankPtr->GetName())
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("tank player controller has no tank!"))
    }
}

void ATankPlayerController::Tick(const float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) return;
    FVector HitLocation;
    if (!GetSightRayHitLocation(HitLocation)) return;
    UE_LOG(LogTemp, Warning, TEXT("%s is aiming towards %s."), *GetControlledTank()->GetName(), *HitLocation.ToString())
    // aim towards HitLocation
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
    // ray cast from TankPlayerUI.AimPoint to World
    // if there is no Hit, return false
    // else set HitLocation and return true
    OutHitLocation = FVector(1.0);
    return true;
}
