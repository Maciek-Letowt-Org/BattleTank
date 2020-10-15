// copyright Maciek Letowt 2020


#include "SprungWheel.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    Body = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
    SetRootComponent(Body);
    Body->SetNotifyRigidBodyCollision(true);
    Body->SetVisibility(false);
    
    Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
    Wheel->SetupAttachment(Body);

    BuildSpringBetweenBodyAndWheel();
}

void ASprungWheel::BuildSpringBetweenBodyAndWheel()
{
    Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
    Spring->SetupAttachment(Body);
    Spring->SetConstrainedComponents(Body, FName("Body"), Wheel, FName("Wheel"));

    Spring->SetLinearDriveParams(PositionStrength, VelocityStrength, 0.f);
    
    // only moves up & down
    Spring->SetLinearPositionDrive(false, false, true);
    Spring->SetLinearVelocityDrive(false, false, true);
    Spring->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 100.f);

    // no sing or twist
    Spring->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
    Spring->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
    Spring->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
