// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * UStaticMeshComponent elevation of tank barrel
 */
UCLASS( meta=(BlueprintSpawnableComponent)) //, HideCategories=("Collision") )
class BATTLETANK_API UTankBarrel final : public UStaticMeshComponent
{
    GENERATED_BODY()
public:
    // -1 is max downward speed. +1 is max upward speed
    void Elevate(float RelativeSpeed);
private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxDegreesPerSecond = 10.f;
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MaxElevationDegrees = 45.f;
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MinElevationDegrees = -4.4f;
};
