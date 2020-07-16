// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"
class UTankTrack;
/**
 * UNavMovementComponent allows fly-by-wire control of tank tracks
 */
UCLASS( meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent final : public UNavMovementComponent
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category=Setup)
    void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
    UFUNCTION(BlueprintCallable, Category=Input)
    void IntendMoveForward(float Throw) const;
    UFUNCTION(BlueprintCallable, Category=Input)
    void IntendTurnRight(float Throw) const;

    // todo check protection level
    /** path following: request new velocity */
    virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
private:

    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightTrack = nullptr;
};
