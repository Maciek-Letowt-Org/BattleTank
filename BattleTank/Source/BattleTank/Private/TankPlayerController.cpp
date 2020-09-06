// copyright Maciek Letowt 2020
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

    if (ensure(AimingComponent))
    {
        FoundAimingComponent(AimingComponent);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("tank player controller has no aiming component!"))
    }
}

void ATankPlayerController::Tick(const float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() const
{
    if (AimingComponent)
    {
        FVector OutHitLocation;
        if (GetSightRayHitLocation(OutHitLocation))
        {
            // aim towards Hit Location
            AimingComponent->AimAt(OutHitLocation);
        }
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // find crosshair position in pixel coordinates
    int32 OutViewPortSizeX, OutViewPortSizeY;
    GetViewportSize(OutViewPortSizeX, OutViewPortSizeY);

    if (OutViewPortSizeX == 0 || OutViewPortSizeY == 0)
    {
        return false;
    }

    // "De-Project" the screen position of the crosshair to "look direction"
    const FVector2D ScreenLocation = FVector2D(CrossHairXLocation * OutViewPortSizeX,
                                               CrossHairYLocation * OutViewPortSizeY);
    FVector OutLookDirection;
    if (GetLookDirection(ScreenLocation, OutLookDirection))
    {
        // return result from ray cast in "look direction" from camera to World
        return GetLookVectorHitLocation(OutLookDirection, OutHitLocation);
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D ScreenLocation, FVector& OutLookDirection) const
{
    FVector OutCameraLocation;

    const bool bFoundDirection = DeprojectScreenPositionToWorld
    (
        ScreenLocation.X,
        ScreenLocation.Y,
        OutCameraLocation,
        OutLookDirection
    );

    return bFoundDirection;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookFrom, FVector& OutHitLocation) const
{
    FHitResult OutHitResult;
    const FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    const FVector EndLocation = StartLocation + (LookFrom * LineTraceRange);

    // see what is hit up to max. range
    const bool bHit = GetWorld()->LineTraceSingleByChannel(
        OutHitResult,
        StartLocation,
        EndLocation,
        ECC_Visibility
    );

    if (bHit)
    {
        // set HitLocation
        OutHitLocation = OutHitResult.Location;
    }

    return bHit;
}
