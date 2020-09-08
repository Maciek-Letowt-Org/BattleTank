// copyright Maciek Letowt 2020
#include "TankTrack.h"
// Sets default values for this component's properties
UTankTrack::UTankTrack()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
    const auto TankBody = GetOwner()->GetRootComponent();
    
    if (!ensure(TankBody))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s track %s cannot find a tank body!"), *GetOwner()->GetName(), *GetName());
        return;
    }
    TankRoot = Cast<UStaticMeshComponent>(TankBody);
}

void UTankTrack::TickComponent(const float DeltaTime, const ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!ensure(TankRoot))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s track %s cannot tick a tank body!"), *GetOwner()->GetName(), *GetName());
        return;
    }
    // correct sidewards slippage
    const FVector SlippageUnitVector = GetRightVector();
    const float SlippageSpeed = FVector::DotProduct(SlippageUnitVector, GetComponentVelocity());
    const FVector SlippageVelocity = SlippageSpeed * SlippageUnitVector;
    // a = v/t
    const FVector SlippageAcceleration = SlippageVelocity / DeltaTime;
    const FVector CorrectionAcceleration = SlippageAcceleration * -1;
    // F = m.a for 2 tracks
    const FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;
    TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) const
{
    if (!ensure(TankRoot))
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s track %s cannot throttle a tank body!"), *GetOwner()->GetName(), *GetName());
        return;
    }
    Throttle = FMath::Clamp<float>(Throttle, -1.f, +1.f);
    const FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    const FVector ForceLocation = GetComponentLocation();
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
