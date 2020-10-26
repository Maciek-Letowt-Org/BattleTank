// copyright Maciek Letowt 2020
#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
    Super::BeginPlay();

    // add a sprung wheel
    SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
    if (!SpawnedActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s cannot spawn a wheel"), *GetOwner()->GetName());
        return;
    }
    SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
    UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}


// Called every frame
void USpawnPoint::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}
