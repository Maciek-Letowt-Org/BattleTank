// copyright Maciek Letowt 2020


#include "Tank.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"

void ATank::BeginPlay()
{
    Super::BeginPlay();
 //   TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

// Sets default values
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    if (RateOfFire <= 0.f)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s has no positive rate of fire! Set to 1"), *GetName());
        RateOfFire = 1;
    }
    ReloadTimeInSeconds = 60 / RateOfFire;
}

void ATank::Fire()
{
    if (!ensure(Barrel))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s has no barrel to fire!"), *GetName());
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

