// copyright Maciek Letowt 2020
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank final : public APawn
{
    GENERATED_BODY()
public:
    // Sets default values for this pawn's properties
    ATank();

    // called by engine
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                             AActor* DamageCauser) override;
private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100; // percent healthy at start

    UPROPERTY(VisibleAnywhere, Category = "Health")
    int32 CurrentHealth = StartingHealth; // percent healthy during play

};
