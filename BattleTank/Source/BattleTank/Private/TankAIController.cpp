// copyright Maciek Letowt 2020

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

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

    //fire if ready
    AimingComponent->Fire();
}
