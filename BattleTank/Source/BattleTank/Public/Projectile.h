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

    void LaunchProjectile(float Speed) const;

private:
    virtual void BeginPlay() override;
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
               FVector NormalImpulse, const FHitResult& Hit);
    void OnTimerExpire();
    // ------ members / properties -------------------------------
    class UProjectileMovementComponent* ProjectileMovement = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float DestroyDelay = 10.f; // 1 second

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float ProjectileDamage = 20.f; // health removed by 1 projectile hit

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* CollisionMesh = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UParticleSystemComponent* LaunchBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UParticleSystemComponent* ImpactBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class URadialForceComponent* ExplosionForce = nullptr;
};
