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
    AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
    if (!NewActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("tank %s cannot spawn a wheel"), *GetOwner()->GetName());
        return;
    }
    NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
    UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}
