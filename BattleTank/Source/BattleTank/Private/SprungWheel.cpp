// copyright Maciek Letowt 2020


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// set up mass with wheel & constraint
ASprungWheel::ASprungWheel()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
    SetRootComponent(MassWheelConstraint);

    Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
    Mass->SetupAttachment(MassWheelConstraint);

    Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
    Wheel->SetupAttachment(MassWheelConstraint);
}


// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
    Super::BeginPlay();
    if (GetAttachParentActor())
    {
        UE_LOG(LogTemp, Warning, TEXT("not null"))
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("it is null"))
    };
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
