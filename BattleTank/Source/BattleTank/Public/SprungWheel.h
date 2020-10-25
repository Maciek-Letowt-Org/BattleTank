// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel final : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ASprungWheel();

    // Called every frame
    virtual void Tick(float DeltaTime) override;
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
private:
    void SetupConstraint();
    // ------ members / properties -------------------------------
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float PositionStrength = 1000.f;
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float VelocityStrength = 100.f;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USphereComponent* Axle = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class USphereComponent* Wheel = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UPhysicsConstraintComponent* MassAxleConstraint = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
};
