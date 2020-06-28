// copyright Maciek Letowt 2020


#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankMovementComponent.h"
#include "TankTurret.h"

// Sets default values
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    //no need to protect pointer as added at construction
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));

    // no longer need as now blue print spawn-able
    //TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("MovementComponent"));

    if (RateOfFire <= 0.f)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s has no positive rate of fire!"), *GetOwner()->GetName());
        RateOfFire = 1;
    }
    ReloadTimeInSeconds = 60 / RateOfFire;
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    if (!BarrelToSet)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s has no barrel to set!"), *GetOwner()->GetName());
        return;
    }

    TankAimingComponent->SetBarrelReference(BarrelToSet);
    Barrel = BarrelToSet;
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

void ATank::Fire()
{
    if (!Barrel)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s has no barrel to fire!"), *GetOwner()->GetName());
        return;
    }

    const bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds);

    if (bIsReloaded)
    {
        const FVector Loc = Barrel->GetSocketLocation(FName("Projectile"));
        const FRotator Rot = Barrel->GetSocketRotation(FName("Projectile"));

        AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBluePrint,
            Loc,
            Rot
        );

        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
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
