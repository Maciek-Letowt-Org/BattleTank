// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
class AProjectile; // FD
class UTankBarrel; // Forward Declaration instead of include
class UTankTurret; // Forward Declaration instead of include
UCLASS()
class BATTLETANK_API ATank final : public APawn
{
    GENERATED_BODY()
public:
    void AimAt(FVector HitLocation) const;

    UFUNCTION(BlueprintCallable, Category=Setup)
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    UFUNCTION(BlueprintCallable, Category=Setup)
    void SetTurretReference(UTankTurret* TurretToSet) const;
    UFUNCTION(BlueprintCallable, Category=Firing)
    void Fire() const;
protected:
    class UTankAimingComponent* TankAimingComponent = nullptr;
private:
    // Sets default values for this pawn's properties

    ATank();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, Category=Firing)
    float LaunchSpeed = 2000; // = 2000 m/s

    UPROPERTY(EditAnywhere, Category=Setup)
    TSubclassOf<AProjectile> ProjectileBluePrint; // unsafe Alternative = UClass*
    //UClass* ProjectileBluePrint = nullptr; // unsafe - makes editor crash

    
    // local barrel reference for spawning projectile
    UTankBarrel* Barrel = nullptr;
};
