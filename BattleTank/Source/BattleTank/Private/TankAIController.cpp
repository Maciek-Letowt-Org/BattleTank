// copyright Maciek Letowt 2020

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);

    if (InPawn)
    {
        ATank* PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank))
        {
            return;
        }
        //TODO subscribe to death event
    }
}

void ATankAIController::Tick(const float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

    if (!ensure(PlayerTank))
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller %s cannot find PLAYER tank!"), *GetPawn()->GetName());
        return;
    }

    const auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

    if (!ensure(AimingComponent))
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller %s has no aiming component!"), *GetPawn()->GetName());
        return;
    }

    // move towards player
    MoveToActor(PlayerTank, AcceptanceRadius);

    // aim towards player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    //fire if aim locked
    if (AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire();
    }
}
