// Shooth Them Up Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUHealthComponent();
    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintCallable, Category="Health")
    bool IsDead() const {return FMath::IsNearlyZero(Health); }
    
    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;
protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta=(ClampMin="0.0", ClampMax="1000.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal")
    bool AutoHeal = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta=(EditCondition = "AutoHeal", ClampMin="0.0", ClampMax="1000.0"))
    float HealDelay = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta=(EditCondition = "AutoHeal",ClampMin="0.0", ClampMax="100.0"))
    float HealUpdateTime = 1.0f;
    

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Heal", meta=(EditCondition = "AutoHeal",ClampMin="0.0", ClampMax="10.0"))
    float HealModifier = 1.0;
       
    
private:
    float Health = 0.0f;
    FTimerHandle HealTimerHandle;
    void HealUpdate();
    void SetHealth (float NewHealth);
    
    UFUNCTION()
    void OnTakeAnyDamageHandle
    (AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
