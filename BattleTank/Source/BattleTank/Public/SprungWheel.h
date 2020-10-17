// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
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

    // ------ members / properties -------------------------------
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float PositionStrength = 1000.f;
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float VelocityStrength = 100.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float MassMassInKg = 1000.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float WheelMassInKg = 50.f;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* Mass = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* Wheel = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UPhysicsConstraintComponent* MassWheelConstraint = nullptr;
};
