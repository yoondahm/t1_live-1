// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/T2Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/T2AttributeComponent.h"
#include "UI/T2PlayerHudWidget.h"

// Sets default values
AT2Character::AT2Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	AttributeComponent = CreateDefaultSubobject<UT2AttributeComponent>(TEXT("Attribute"));
}

// Called when the game starts or when spawned
void AT2Character::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
	if (PlayerController)
	{
		auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PlayerController->GetLocalPlayer());

		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	if (PlayerHudWidgetClass)
	{
		PlayerHudWidget = CreateWidget<UT2PlayerHudWidget>(GetWorld(), PlayerHudWidgetClass);
		
		if (PlayerHudWidget)
		{
			PlayerHudWidget->AddToViewport();
		}
	}
}

// Called every frame
void AT2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Cyan,
	                                 FString::Printf(TEXT("Stamina: %f"), AttributeComponent->GetBASEStamina()));
	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Cyan,
	                                 FString::Printf(TEXT("MaxWalkSpeed: %f"), GetCharacterMovement()->MaxWalkSpeed));
}

// Called to bind functionality to input
void AT2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AT2Character::Input_Move);
		// 명시?
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AT2Character::Input_Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AT2Character::Sprinting);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AT2Character::StopSprinting);
	}
}

bool AT2Character::IsMoving() const
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		return MovementComponent->Velocity.Size2D() > 3.0f && MovementComponent->GetCurrentAcceleration() !=
			FVector::ZeroVector;
	}

	return false;
}

void AT2Character::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 행렬 어려우으...
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardVector, MovementVector.X);
	AddMovementInput(RightVector, MovementVector.Y);
}

void AT2Character::Input_Look(const FInputActionValue& InputValue)
{
	FVector2D LookVector = InputValue.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void AT2Character::Sprinting()
{
	check(AttributeComponent);
	if (IsMoving() && AttributeComponent->CheckHasEnoughStamina(SprintingStamina))
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;

		AttributeComponent->ToggleStaminaRegen(false);

		AttributeComponent->DecreaseStamina(SprintingStamina);
	}
	else
	{
		StopSprinting();
	}
}

void AT2Character::StopSprinting()
{
	check(AttributeComponent);
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	AttributeComponent->ToggleStaminaRegen(true, 1.0f);
}
