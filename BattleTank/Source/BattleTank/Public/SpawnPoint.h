// copyright Maciek Letowt 2020
#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint final : public USceneComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    USpawnPoint();
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

    AActor* GetSpawnedActor() const
    {
        return SpawnedActor;
    }

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
private:
    UFUNCTION(BlueprintCallable, Category="Setup") // created this method for the construction script in the blueprint
    void SetSpawnClassBluePrint(const TSubclassOf<AActor> SpawnClassBP)
    {
        SpawnClass = SpawnClassBP;
    }

    // ------ members / properties -------------------------------
    UPROPERTY(EditDefaultsOnly, Category="Setup")
    TSubclassOf<AActor> SpawnClass;
    AActor* SpawnedActor = nullptr;
};
