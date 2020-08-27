// copyright Maciek Letowt 2020


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(const float Throw) const
{
    if (!LeftTrack || !RightTrack)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no track to move!"), *GetOwner()->GetName());
        return;
    }

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(const float Throw) const
{
    if (!LeftTrack || !RightTrack)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s aiming component has no track to turn!"), *GetOwner()->GetName());
        return;
    }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    const FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal(); // where it is headed
    const FVector AIForwardIntention = MoveVelocity.GetSafeNormal(); // where it wants to go
    const float RightThrow = FVector::CrossProduct(AIForwardIntention,TankForward).Z;
    IntendTurnRight(RightThrow);
    const float ForwardThrow = FVector::DotProduct(AIForwardIntention,TankForward );
    IntendMoveForward(ForwardThrow);
}
