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
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller %s cannot find AI tank!"));
        return;
    }

    ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller %s cannot find PLAYER tank!"), *GetPawn()->GetName());
        return;
    }

    //todo move towards player

    ControlledTank->AimAt(PlayerTank->GetActorLocation());
    //fire if ready
    ControlledTank->Fire();
}
