// copyright Maciek Letowt 2020


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
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

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();
    // prevents AI from firing as soon as the game starts
    LastFireTime = GetWorld()->GetTimeSeconds();
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
    return RoundsLeft;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    if (!ensure(BarrelToSet))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no barrel to set!"), *GetOwner()->GetName());
        return;
    }

    if (!ensure(TurretToSet))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no turret to set!"), *GetOwner()->GetName());
        return;
    }

    Barrel = BarrelToSet;
    Turret = TurretToSet;

    if (RateOfFire <= 0.f)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no positive rate of fire! Set to 1"),
               *GetOwner()->GetName());
        RateOfFire = 1;
    }
    ReloadTimeInSeconds = 60 / RateOfFire;
}

void UTankAimingComponent::AimAt(const FVector HitLocation)
{
    if (!ensure(Barrel))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no barrel to aim!"), *GetOwner()->GetName());
        return;
    }

    if (!ensure(Turret))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no turret to aim!"), *GetOwner()->GetName());
        return;
    }

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
    const FRotator AimRtt = AimDirection.Rotation().Clamp();

    //TODO Roll: 0 Pitch & Yaw unchanged; +90 p=y but y=-p; +-180 * -1; -90 y=p but p=-y
    const float RollRadians = Turret->GetComponentTransform().GetRotation().Y;
    const float RollDegrees = FMath::RadiansToDegrees(RollRadians);
    const float Roll = FMath::UnwindDegrees(RollDegrees);
    //const float RelativePitch = 
    
    UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component roll %f"), *GetOwner()->GetName(),Roll);
    MoveBarrelTowards(AimRtt.Pitch);
    MoveTurretTowards(AimRtt.Yaw);
}

void UTankAimingComponent::MoveBarrelTowards(const float AimPitch)
{
    if (!ensure(Barrel))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no barrel to move!"), *GetOwner()->GetName());
        return;
    }

    // work out rotation difference between current barrel rotation & aim direction rotation
    const float BarrelPitch = Barrel->GetForwardVector().Rotation().Clamp().Pitch;
    const float DeltaPitch = AimPitch - BarrelPitch;

    if (abs(DeltaPitch) > AimTolerance)
    {
        bBarrelMoving = true;
        Barrel->Elevate(FMath::UnwindDegrees(DeltaPitch));
    }
    else
    {
        bBarrelMoving = false;
    }
}

void UTankAimingComponent::MoveTurretTowards(const float AimYaw)
{
    if (!ensure(Turret))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no turret to move!"), *GetOwner()->GetName());
        return;
    }

    // work out rotation difference between current turret rotation & aim direction rotation
    const float TurretYaw = Turret->GetForwardVector().Rotation().Clamp().Yaw;
    const float DeltaYaw = AimYaw - TurretYaw;

    if (abs(DeltaYaw) > AimTolerance)
    {
        bTurretMoving = true;
        Turret->Rotate(FMath::UnwindDegrees(DeltaYaw));
    }
    else
    {
        bTurretMoving = false;
    }
}

void UTankAimingComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (RoundsLeft < 1)
    {
        FiringState = EFiringState::NoAmmo;
    }
    else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (bBarrelMoving || bTurretMoving)
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }
}

void UTankAimingComponent::Fire()
{
    // only fire if locked or reloading
    if (FiringState == EFiringState::Reloading || FiringState == EFiringState::NoAmmo)
    {
        return;
    }

    if (!ensure(Barrel))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no barrel to fire!"), *GetOwner()->GetName());
        return;
    }

    if (!ensure(ProjectileBluePrint))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no projectile blueprint!"),
               *GetOwner()->GetName());
        return;
    }

    const FVector Loc = Barrel->GetSocketLocation(FName("Projectile"));
    const FRotator Rot = Barrel->GetSocketRotation(FName("Projectile"));

    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
        ProjectileBluePrint,
        Loc,
        Rot
    );

    Projectile->LaunchProjectile(LaunchSpeed);
    LastFireTime = GetWorld()->GetTimeSeconds();
    RoundsLeft--;
}
