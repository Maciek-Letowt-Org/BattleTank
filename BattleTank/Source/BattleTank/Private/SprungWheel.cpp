// copyright Maciek Letowt 2020
#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// set up mass with wheel & constraint
ASprungWheel::ASprungWheel()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassAxleConstraint"));
    SetRootComponent(MassAxleConstraint);

    Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
    Axle->SetupAttachment(MassAxleConstraint);

    Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
    Wheel->SetupAttachment(Axle);

    AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
    AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
    Super::BeginPlay();
    SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
    if (!GetAttachParentActor())
    {
        UE_LOG(LogTemp, Warning, TEXT("%s cannot find a parent"), *GetName());
        return;
    }

    UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

    if (!BodyRoot)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s cannot find a parent body"), *GetName());
        return;
    }
    MassAxleConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
    AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASprungWheel::AddDrivingForce(const float ForceMagnitude) const
{
    Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}
