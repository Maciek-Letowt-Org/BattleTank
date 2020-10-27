// copyright Maciek Letowt 2020
#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// set up mass with wheel & constraint
ASprungWheel::ASprungWheel()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // tick after hitting the ground
    PrimaryActorTick.TickGroup = TG_PostPhysics;

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
    Wheel->SetNotifyRigidBodyCollision(true);
    Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
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
    if (GetWorld()->TickGroup == TG_PostPhysics)
    {
        TotalForceMagnitudeThisFrame = 0.f;
    }
}

void ASprungWheel::AddDrivingForce(const float ForceMagnitude)
{
    TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                         FVector NormalImpulse, const FHitResult& Hit)
{
    ApplyForce();
}

void ASprungWheel::ApplyForce() const
{
    Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}
