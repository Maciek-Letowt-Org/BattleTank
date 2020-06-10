// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * UStaticMeshComponent rotation of tank turret 
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	public:
        // -1 is max anticlockwise speed. +1 is max clockwise speed
        void Rotate(float RelativeSpeed);
	private:
        UPROPERTY(EditAnywhere, Category = Setup)
        float MaxDegreesPerSecond = 5.f;
};
