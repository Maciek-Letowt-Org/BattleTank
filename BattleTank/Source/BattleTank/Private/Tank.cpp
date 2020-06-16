// copyright Maciek Letowt 2020


#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    //no need to protect pointer as added at construction
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) const
{
    if (!BarrelToSet)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s has no barrel to set!"), *GetOwner()->GetName());
        return;
    }

    TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) const
{
    if (!TurretToSet)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s has no turret to set!"), *GetOwner()->GetName());
        return;
    }

    TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire() const
{
    const auto TankName = GetOwner()->GetName();
    const auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: %s FIRE!"), Time, *TankName);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (!PlayerInputComponent) return;
    
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(const FVector HitLocation) const
{
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
