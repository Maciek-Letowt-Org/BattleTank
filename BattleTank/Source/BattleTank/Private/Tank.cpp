// copyright Maciek Letowt 2020
#include "Tank.h"

// Sets default values
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

float ATank::GetHealthPercent() const
{
    return static_cast<float>(CurrentHealth) / static_cast<float>(StartingHealth);
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                        AActor* DamageCauser)
{
    const int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    const int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
    UE_LOG(LogTemp, Warning, TEXT("tank %s with health %i was damaged by %i but took %i"), *GetName(),
           CurrentHealth, DamagePoints, DamageToApply);

    CurrentHealth -= DamageToApply;
    return DamageToApply;
}
