// copyright Maciek Letowt 2020


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    if (!BarrelToSet)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no barrel to set!"), *GetOwner()->GetName());
        return;
    }

    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
    if (!TurretToSet)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no turret to set!"), *GetOwner()->GetName());
        return;
    }

    Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(const FVector HitLocation, const float LaunchSpeed) const
{
    if (!Barrel) return;
    if (!Turret) return;

    const FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    FVector OutLaunchVelocity;

    const bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
        this,
        OutLaunchVelocity,
        StartLocation,
        HitLocation,
        LaunchSpeed,
        false,
        0.f,
        0.f,
        ESuggestProjVelocityTraceOption::DoNotTrace // parameter must be present to work around bug in UE4.25
    );

    if (!bHaveAimSolution)
    {
        return;
    }

    const FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
    const FRotator AimRtt = AimDirection.Rotation();

    const auto TankName = GetOwner()->GetName();
    const auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: %s aiming towards %s"), Time, *TankName, *AimRtt.ToString());

    MoveBarrelTowards(AimRtt);
    MoveTurretTowards(AimRtt);
}

void UTankAimingComponent::MoveBarrelTowards(const FRotator AimRtt) const
{
    // work out rotation difference between current barrel rotation & aim direction rotation
    const FRotator BarrelRtt = Barrel->GetForwardVector().Rotation();
    const FRotator DeltaRtt = AimRtt - BarrelRtt;

    Barrel->Elevate(DeltaRtt.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(const FRotator AimRtt) const
{
    // work out rotation difference between current turret rotation & aim direction rotation
    const FRotator TurretRtt = Turret->GetForwardVector().Rotation();
    const FRotator DeltaRtt = AimRtt - TurretRtt;

    Turret->Rotate(DeltaRtt.Yaw);
}
