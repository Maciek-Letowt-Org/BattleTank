// copyright Maciek Letowt 2020


#include "TankTrack.h"

void UTankTrack::SetThrottle(const float Throttle) const
{


    // TODO clamp throttle

    const FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    const FVector ForceLocation = GetComponentLocation();
    UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
