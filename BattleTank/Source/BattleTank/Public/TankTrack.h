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
    void SetThrottle(float Throttle);

    // ------ members / properties -------------------------------
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 50000000.f; // force in Newtons
private:
    UTankTrack();

    virtual void BeginPlay() override;
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
               FVector NormalImpulse, const FHitResult& Hit);
    void ApplySidewaysForce();
    void DriveTrack() const;
    // ------ members / properties -------------------------------
    float CurrentThrottle = 0.f;
};
