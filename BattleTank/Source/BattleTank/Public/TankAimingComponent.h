// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UTankAimingComponent();
    void SetBarrelReference(UStaticMeshComponent* BarrelToSet);
    void AimAt(const FVector HitLocation, float LaunchSpeed);
private:
    UStaticMeshComponent* Barrel = nullptr;
    void MoveBarrelTowards(FVector AimDirection);
};
