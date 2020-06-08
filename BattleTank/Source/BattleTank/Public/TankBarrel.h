// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * UStaticMeshComponent elevation of tank barrel
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
    GENERATED_BODY()
public:
    // -1 is max downward speed. +1 is max upward speed
    void Elevate(float RelativeSpeed);
private:
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegreesPerSecond = 5.f;
    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxElevationDegrees = 45.f;
    UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevationDegrees = -4.4f;
};
