// copyright Maciek Letowt 2020
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    // move the turret right amount this frame, given:
    // max elevation speed, frame time
    const float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    const float NewRotation = GetRelativeRotation().Yaw + RotationChange;
    
    SetRelativeRotation(FRotator(0.f, NewRotation, 0.f));
};

