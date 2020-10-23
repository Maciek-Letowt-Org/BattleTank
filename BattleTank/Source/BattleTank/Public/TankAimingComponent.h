// copyright Maciek Letowt 2020
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked,
    NoAmmo
};

class UTankBarrel; // Forward Declaration instead of include
class UTankTurret; // Forward Declaration instead of include
class AProjectile; // FD
/**
* UActorComponent holds turret & barrel parameters 
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent final : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    void AimTowardsSolution(FVector LaunchVelocity);
    void AimAt(FVector HitLocation);
    UFUNCTION(BlueprintCallable, Category="Firing")
    void Fire();

    EFiringState GetFiringState() const;

    UFUNCTION(BlueprintCallable, Category="Firing")
    int32 GetRoundsLeft() const;

protected:
    UPROPERTY(BlueprintReadOnly, Category="State")
    EFiringState FiringState = EFiringState::Reloading;

private:

    // Sets default values for this component's properties
    UTankAimingComponent();
    void MoveBarrelTowards(float AimPitch);
    void MoveTurretTowards(float AimYaw);
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category="Setup") // created this method for the construction script in the blueprint
    void SetProjectileBluePrint(const TSubclassOf<AProjectile> ProjectileBP)
    {
        ProjectileBluePrint = ProjectileBP;
    }

    // ------ members / properties -------------------------------
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    bool bIsBarrelMoving = false;
    bool bIsTurretMoving = false;

    UPROPERTY(EditDefaultsOnly, Category="Firing")
    int32 RoundsLeft = 99; // rounds on board

    UPROPERTY(EditDefaultsOnly, Category="Firing")
    float AimTolerance = 0.01; // degrees from crosshair target

    UPROPERTY(EditDefaultsOnly, Category="Firing")
    float LaunchSpeed = 8000; // = 8000 m/s

    UPROPERTY(EditDefaultsOnly, Category="Firing")
    int32 RateOfFire = 30; // rounds per minute
    double ReloadTimeInSeconds = 0; // 60/RateOfFire
    double LastFireTime = 0; // time seconds of last fire

    UPROPERTY(EditDefaultsOnly, Category="Setup")
    TSubclassOf<AProjectile> ProjectileBluePrint;

    //UClass* ProjectileBluePrint = nullptr; // unsafe - makes editor crash
};
