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
    Locked
};

class UTankBarrel; // Forward Declaration instead of include
class UTankTurret; // Forward Declaration instead of include
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
    void AimAt(FVector HitLocation) const;

protected:
    UPROPERTY(BlueprintReadOnly, Category="State")
    EFiringState FiringState = EFiringState::Aiming;

private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category="Firing")
    float LaunchSpeed = 2000; // = 2000 m/s

    void MoveBarrelTowards(FRotator AimRtt) const;
    void MoveTurretTowards(FRotator AimRtt) const;
};
