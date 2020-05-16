// copyright Maciek Letowt 2020


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    // logs computerNameHexWord
    UE_LOG(LogTemp, Warning, TEXT("tank ai controller pawn %s"), *GetPawn()->GetHumanReadableName());;
    ATank* TankPtr = GetPlayerTank();
    if (TankPtr)
    {
        UE_LOG(LogTemp, Warning, TEXT("ai controller found player tank %s"), *TankPtr->GetName())
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ai controller cannot find player tank!"))
   }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerTank() const
{
    APlayerController* Controller = GetWorld()->GetFirstPlayerController();
    if (!Controller) return nullptr;
    APawn* Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;
    return Cast<ATank>(Pawn);
}

