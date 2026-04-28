// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T2Define.h"
#include "Components/ActorComponent.h"
#include "T2AttributeComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAttributeChanged, ET2AttributeType, float)
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class T2_API UT2AttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UT2AttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE float GetBASEStamina() const { return BaseStamina; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }

	bool CheckHasEnoughStamina(float StaminaCost) const;

	void DecreaseStamina(float Stamina);

	void ToggleStaminaRegen(bool bEnabled, float startDelay = 2.0f);
	
	void RegenStaminaHandler();
	
public:
	void BroadcastAttributeChanged(ET2AttributeType InAttributeType) const;
	
public:
	FOnAttributeChanged OnAttributeChanged;

protected:
	UPROPERTY(EditAnywhere, Category=Stamina)
	float BaseStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category=Stamina)
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, Category=Stamina)
	float StaminaRegenRate = 0.2f;

	UPROPERTY(EditAnywhere, Category=Stamina)
	float StaminaRegenTime = 0.1;

	FTimerHandle StaminaRegenTimer;
};
