// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/T2AttributeComponent.h"

// Sets default values for this component's properties
UT2AttributeComponent::UT2AttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UT2AttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UT2AttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UT2AttributeComponent::CheckHasEnoughStamina(float StaminaCost) const
{
	return BaseStamina >= StaminaCost;
}

void UT2AttributeComponent::DecreaseStamina(float Stamina)
{
	BaseStamina = FMath::Clamp(BaseStamina - Stamina, 0.0f, MaxStamina);
}

void UT2AttributeComponent::ToggleStaminaRegen(bool bEnabled, float startDelay)
{
	if (bEnabled)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(StaminaRegenTimer))
		{
			GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimer, this, &UT2AttributeComponent::RegenStaminaHandler,
			                                       StaminaRegenTime, true,
			                                       startDelay);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRegenTimer);
	}
}

void UT2AttributeComponent::RegenStaminaHandler()
{
	BaseStamina = FMath::Clamp(BaseStamina + StaminaRegenRate, 0.0f, MaxStamina);
	
	if (BaseStamina >= MaxStamina)
	{
		ToggleStaminaRegen(false);
	}
}
