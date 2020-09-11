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

    // ------ members / properties -------------------------------
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 50000.f; // force in Newtons
private:
    UTankTrack();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;
    virtual void BeginPlay() override;
    UFUNCTION(BlueprintCallable, Category="Firing")
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
               FVector NormalImpulse, const FHitResult& Hit);
    // ------ members / properties -------------------------------
    // UStaticMeshComponent* TankRoot = nullptr;
};
