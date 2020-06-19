// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile final : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AProjectile();

    // Called every frame
    void Tick(float DeltaTime) override;
    void LaunchProjectile(float Speed);
protected:
    // Called when the game starts or when spawned
    void BeginPlay() override;
private:
    class UProjectileMovementComponent* ProjectileMovement = nullptr;
};