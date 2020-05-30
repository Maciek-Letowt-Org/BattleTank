// copyright Maciek Letowt 2020


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
    Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(const FVector HitLocation, const float LaunchSpeed)
{
    if (!Barrel) return;

    const FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    FVector OutLaunchVelocity;

    const bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
        this,
        OutLaunchVelocity,
        StartLocation,
        HitLocation,
        LaunchSpeed,
        ESuggestProjVelocityTraceOption::DoNotTrace
    );

    if (!bHaveAimSolution) return;

    const auto AimDirection = OutLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
}

void UTankAimingComponent::MoveBarrelTowards(const FVector AimDirection)
{
    // work out difference between current barrel rotation & aim direction
    auto BarrelRtt = Barrel->GetForwardVector().Rotation();
    auto AimRtt = AimDirection.Rotation();
    const auto TankName = GetOwner()->GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s wants to aim in %s direction, but barrel is stuck at %s."), *TankName,
           *AimRtt.ToString(), *BarrelRtt.ToString());

    auto DeltaRtt = AimRtt - BarrelRtt;

    // move the barrel the right amount this frame, give:
    // max elevation speed, frame time
    
    
    // get rotation from out launch v
    // start moving y-rot of barrel to y-rot of launch v
    // start moving z-rot of turret to z-rot of launch v
}
