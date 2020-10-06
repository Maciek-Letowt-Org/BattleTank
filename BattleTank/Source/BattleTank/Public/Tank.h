// copyright Maciek Letowt 2020
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank final : public APawn
{
    GENERATED_BODY()
public:
    // return current health as a percentage of starting health, between 0 and 1.
    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealthPercent() const;

    // called by engine
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                             AActor* DamageCauser) override;

    //--------------- members & properties --------------------
    FTankDelegate OnDeath;

private:
    // Sets default values for this pawn's properties
    ATank();

    //--------------- members & properties --------------------
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100; // percent healthy at start

    UPROPERTY(VisibleAnywhere, Category = "Health")
    int32 CurrentHealth = 0; // percent healthy during play
};
