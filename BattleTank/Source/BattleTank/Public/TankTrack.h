// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * UStaticMeshComponent for max. driving force and apply forces to the tank
 */
UCLASS( meta=(BlueprintSpawnableComponent))

class BATTLETANK_API UTankTrack final : public UStaticMeshComponent
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Input")
    void SetThrottle(float Throttle) const;

    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 50000.f; // force in Newtons 
};
