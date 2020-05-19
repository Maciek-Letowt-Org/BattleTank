// copyright Maciek Letowt 2020


#include "TankPlayerController.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"

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

void ATankPlayerController::AimTowardsCrosshair() const
{
    if (!GetControlledTank()) return;
    FVector HitLocation;
    if (!GetSightRayHitLocation(HitLocation)) return;
    
    // aim towards HitLocation
    GetControlledTank()->AimAt(HitLocation);
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

    // "De-Project" the screen position of the crosshair to "look direction"
    const FVector2D ScreenLocation = FVector2D(CrossHairXLocation * OutViewPortSizeX,
                                               CrossHairYLocation * OutViewPortSizeY);
    FVector OutLookDirection;
    if (!GetLookDirection(ScreenLocation, OutLookDirection)) return false;

    // ray cast in "look direction" from camera to World
    if (GetLookVectorHitLocation(OutLookDirection, OutHitLocation)) return true;

    // if there is no Hit, return false
    return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D ScreenLocation, FVector& OutLookDirection) const
{
    FVector OutCameraLocation;

    return DeprojectScreenPositionToWorld
    (
        ScreenLocation.X,
        ScreenLocation.Y,
        OutCameraLocation,
        OutLookDirection
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection, FVector& OutHitLocation) const
{
    // collision query parameters: defaultName, don't go through glass, ignore self
    const FCollisionQueryParams CollisionQueryParams(
        FName(TEXT("")),
        false,
        GetControlledTank()
    );
    FHitResult OutHitResult;
    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

    // see what is hit up to max. range
    const bool bHit = GetWorld()->LineTraceSingleByChannel(
        OutHitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility,
        CollisionQueryParams,
        FCollisionResponseParams::DefaultResponseParam
    );
    if (bHit)
    {
        // set HitLocation and return true
        OutHitLocation = OutHitResult.Location;
        return true;
    }
    return false;
}
