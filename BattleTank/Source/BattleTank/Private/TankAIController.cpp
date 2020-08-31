// copyright Maciek Letowt 2020


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

// Called when the game starts or when spawned


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(const float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    ATank* ControlledTank = Cast<ATank>(GetPawn());
    if (!ensure(ControlledTank))
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller %s cannot find AI tank!"));
        return;
    }

    ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (!ensure(PlayerTank))
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller %s cannot find PLAYER tank!"), *GetPawn()->GetName());
        return;
    }

    // move towards player
    MoveToActor(PlayerTank, AcceptanceRadius);

    ControlledTank->AimAt(PlayerTank->GetActorLocation());
    //fire if ready
    ControlledTank->Fire();
}
