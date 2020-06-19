// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
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
    // Sets default values for this component's properties
    UTankAimingComponent();
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    void SetTurretReference(UTankTurret* TurretToSet);
    void AimAt(FVector HitLocation, float LaunchSpeed) const;
private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    void MoveBarrelTowards(FRotator AimRtt) const;
    void MoveTurretTowards(FRotator AimRtt) const;
};
