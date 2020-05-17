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
    // aim towards HitLocation
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // find crosshair position in pixel coordinates
    int32 OutViewPortSizeX, OutViewPortSizeY;
    GetViewportSize(OutViewPortSizeX, OutViewPortSizeY);
    if (OutViewPortSizeX == 0 || OutViewPortSizeY == 0) return false;
    // "De-Project" the screen position of the TankPlayerUI.AimPoint to a World direction
    FVector2D ScreenLocation = FVector2D(CrossHairXLocation * OutViewPortSizeX, CrossHairYLocation * OutViewPortSizeY);
    

    // 
    // ray cast in "look direction" from TankPlayerUI.AimPoint to World
    // see what is hit up to max. range
    // if there is no Hit, return false
    // else set HitLocation and return true
    OutHitLocation = FVector(1.0);
    return true;
}
