// copyright Maciek Letowt 2020

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
// Depends on movement component via pathfinding system. Called when the game starts or when spawned


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(const float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    APawn* ControlledTank = GetPawn();

    if (!ensure(ControlledTank))
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller %s has no tank!"));
        return;
    }

    APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!ensure(PlayerTank))
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller %s cannot find PLAYER tank!"), *GetPawn()->GetName());
        return;
    }

    // move towards player
    MoveToActor(PlayerTank, AcceptanceRadius);

    const auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent))
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller %s has no aiming component!"), *GetPawn()->GetName());
        return;
    }
    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    //fire if ready
    Cast<ATank>(ControlledTank)->Fire();
}
