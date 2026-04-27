// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "T2Character.generated.h"

struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class T2_API AT2Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AT2Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	bool IsMoving() const;

protected:
	UPROPERTY(EditAnywhere, Category= Sprinting)
	float SprintingSpeed = 750.0f;

	UPROPERTY(EditAnywhere, Category= Sprinting)
	float NormalSpeed = 300.0f;

	UPROPERTY(EditAnywhere, Category= Sprinting)
	float SprintingStamina = 0.1f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UT2AttributeComponent> AttributeComponent;

#pragma region InputSystem

public:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Look(const FInputActionValue& InputValue);

	void Sprinting();
	void StopSprinting();

protected:
	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category=Input)
	TObjectPtr<UInputAction> SprintAction;
#pragma endregion
};
