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
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
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
        const auto TankName = GetOwner()->GetName();
        const auto Time = GetWorld()->GetTimeSeconds();
        UE_LOG(LogTemp, Warning, TEXT("%f: %s cannot find aim solution."), Time, *TankName);
        return;
    }

    const auto TankName = GetOwner()->GetName();
    const auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: %s wants to elevate barrel."), Time, *TankName);

    const FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
    const FRotator AimRtt = AimDirection.Rotation();

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
