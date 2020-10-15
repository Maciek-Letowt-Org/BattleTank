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
    void BuildSpringBetweenBodyAndWheel();
    // Sets default values for this actor's properties
    ASprungWheel();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
private:
    // ------ members / properties -------------------------------
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float PositionStrength = 1000.f;
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float VelocityStrength = 100.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float BodyMassInKg = 1000.f;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float WheelMassInKg = 50.f;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* Body = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* Wheel = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UPhysicsConstraintComponent* Spring = nullptr;
};
