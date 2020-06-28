// copyright Maciek Letowt 2020


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) const
{
    Throttle = FMath::Clamp<float>(Throttle, -1.f, +1.f);
    const FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    const FVector ForceLocation = GetComponentLocation();
    UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
