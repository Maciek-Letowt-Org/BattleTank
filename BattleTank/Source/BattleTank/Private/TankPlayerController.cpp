// copyright Maciek Letowt 2020
#include "TankPlayerController.h"
#include "Tank.h"
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
void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        ATank* PossessedTank = Cast<ATank>(InPawn);

        if (!ensure(PossessedTank))
        {
            return;
        }
        // subscribe to death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
    }
}

void ATankPlayerController::Tick(const float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() const
{
    if (!GetPawn()) // if player has depossessed tank (aiming component may not be null)
    {
        return;
    }

    if (AimingComponent)
    {
        FVector OutHitLocation;
        const bool bGotHitLocation = GotSightRayHitLocation(OutHitLocation);
         
        if (bGotHitLocation)
        {
            // aim towards Hit Location
            AimingComponent->AimAt(OutHitLocation);
        }
    }
}

bool ATankPlayerController::GotSightRayHitLocation(FVector& OutHitLocation) const
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
    if (GotLookDirection(ScreenLocation, OutLookDirection))
    {
        return GotLookVectorHitLocation(OutLookDirection, OutHitLocation);
    }

    return false;
}

bool ATankPlayerController::GotLookDirection(const FVector2D ScreenLocation, FVector& OutLookDirection) const
{
    FVector OutCameraLocation;

    const bool bHasDirection = DeprojectScreenPositionToWorld
    (
        ScreenLocation.X,
        ScreenLocation.Y,
        OutCameraLocation,
        OutLookDirection
    );

    return bHasDirection;
}

bool ATankPlayerController::GotLookVectorHitLocation(FVector& LookDirection, FVector& OutHitLocation) const
{
    FHitResult OutHitResult;
    const FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    const FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

    // see what is hit up to max. range
    const bool bHasHitLocation = GetWorld()->LineTraceSingleByChannel(
        OutHitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Camera
    );

    if (bHasHitLocation)
    {
        // set HitLocation
        OutHitLocation = OutHitResult.Location;
    }

    return bHasHitLocation;
}

void ATankPlayerController::OnPossessedTankDeath()
{
    StartSpectatingOnly();
}

