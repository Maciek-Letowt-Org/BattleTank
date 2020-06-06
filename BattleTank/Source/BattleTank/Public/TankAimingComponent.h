// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
class UTankBarrel; // Forward Declaration instead of include
/**
* UActorComponent holds barrel parameters 
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UTankAimingComponent();
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    void AimAt(const FVector HitLocation, float LaunchSpeed) const;
private:
    UTankBarrel* Barrel = nullptr;
    void MoveBarrelTowards(FVector AimDirection) const;
};
