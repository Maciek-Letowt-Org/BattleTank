// copyright Maciek Letowt 2020


#include "Tank.h"
#include "GameFramework/Pawn.h"

// Sets default values
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //no need to protect pointer as added at construction
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::SetBarrelReference(UStaticMeshComponent* BarrelToSet) const
{
    TankAimingComponent->SetBarrelReference(BarrelToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ATank::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(const FVector HitLocation) const
{
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
