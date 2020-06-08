// copyright Maciek Letowt 2020


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    // move the barrel the right amount this frame, give:
    // max elevation speed, frame time
    const float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    const float RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
    const float ClampedNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

    SetRelativeRotation(FRotator(ClampedNewElevation, 0.f, 0.f));
 };
