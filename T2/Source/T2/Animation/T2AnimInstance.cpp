// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/T2AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UT2AnimInstance::UT2AnimInstance()
{
}

void UT2AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(TryGetPawnOwner());

	if (Character)
	{
		MovementComponent = Character->GetCharacterMovement();
	}
}

void UT2AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
		return;
	if (MovementComponent == nullptr)
		return;

	Velocity = MovementComponent->Velocity;

	GroundSpeed = Velocity.Size2D();
	bShouldMove = GroundSpeed > 3.0f && MovementComponent->GetCurrentAcceleration() != FVector::ZeroVector;
	
	bIsFalling = MovementComponent->IsFalling();
}
