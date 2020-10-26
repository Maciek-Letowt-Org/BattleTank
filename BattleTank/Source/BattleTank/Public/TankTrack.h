// copyright Maciek Letowt 2020
#pragma once
#include "CoreMinimal.h"

#include "SprungWheel.h"
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

    // ------ members / properties -------------------------------
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 40000000.f; // force in Newtons
private:
    UTankTrack();

    void DriveTrack(float CurrentThrottle) const;

    TArray<class ASprungWheel*> GetWheels() const;

    // ------ members / properties -------------------------------
};
