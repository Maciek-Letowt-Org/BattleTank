// copyright Maciek Letowt 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
class UTankBarrel; // Forward Declaration instead of include
UCLASS()
class BATTLETANK_API ATank : public APawn
{
    GENERATED_BODY()
public:
    void AimAt(FVector HitLocation) const;

    UFUNCTION(BlueprintCallable, Category=Setup)
    void SetBarrelReference(UTankBarrel* BarrelToSet) const;
    
protected:
    class UTankAimingComponent* TankAimingComponent = nullptr;
private:
    // Sets default values for this pawn's properties

    ATank();

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere,Category=Firing)
    float LaunchSpeed = 100000; // = 1000 m/s
};
