// copyright Maciek Letowt 2020
#include "TankTrack.h"

#include "SpawnPoint.h"
#include "SprungWheel.h"
// Sets default values for this component's properties
UTankTrack::UTankTrack()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::DriveTrack(const float CurrentThrottle) const
{
    const float ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
    const auto Wheels = GetWheels();
    const float ForcePerWheel = ForceApplied / Wheels.Num();
    for (ASprungWheel* Wheel : Wheels)
    {
        Wheel->AddDrivingForce(ForcePerWheel);
    }
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
    TArray<ASprungWheel*> ResultArray;
    TArray<USceneComponent*> Children;
    GetChildrenComponents(true, Children);
    for (USceneComponent* Child : Children)
    {
        const auto SpawnPointChild = Cast<USpawnPoint>(Child);
        if (!SpawnPointChild)
        {
            continue;
        }
        AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
        auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
        if (!SprungWheel)
        {
            continue;
        }
        ResultArray.Add(SprungWheel);
    }

    return ResultArray;
}

void UTankTrack::SetThrottle(const float Throttle) const
{
    const float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.f, +1.f);
    DriveTrack(CurrentThrottle);
}
