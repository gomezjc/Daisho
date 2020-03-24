// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DaishoProjectCharacter.h"

#include <string>

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"

//////////////////////////////////////////////////////////////////////////
// ADaishoProjectCharacter

ADaishoProjectCharacter::ADaishoProjectCharacter()
{

	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Set movement values
	bIsMoving = false;
	bIsAccelerating = false;
	bAccelerationFlag = false;
	
	WalkSpeed = 0.0f;
	RunSpeed = 0.0f;
	SprintSpeed = 0.0f;
	
	SpeedWhenStopping = 0.0f;
	CurrentSpeed = 0.0f;
	MaxSpeed = 600.0f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADaishoProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADaishoProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADaishoProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADaishoProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADaishoProjectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADaishoProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADaishoProjectCharacter::TouchStopped);

}


void ADaishoProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ADaishoProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ADaishoProjectCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	bIsMoving = !GetCapsuleComponent()->GetComponentVelocity().Equals(FVector::ZeroVector, 0.0001f);
	bIsAccelerating = GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f;

	// if is not accelerating, must get the last velocity to stop the player and execute the appropriate animation
	if(!bIsAccelerating && bAccelerationFlag)
	{
		SpeedWhenStopping = CurrentSpeed;
		bAccelerationFlag = false;
		UE_LOG(LogTemp, Warning, TEXT("Speed when stopping %f"), SpeedWhenStopping);
	}

	// Set velocity of player
	CurrentSpeed = UKismetMathLibrary::Clamp(GetVelocity().Size(),WalkSpeed,RunSpeed);
	UE_LOG(LogTemp, Warning, TEXT("Current Speed %f"), CurrentSpeed);
	
	// Set The max walk speed of player for Walk, Run and Sprint actions
	GetCharacterMovement()->MaxWalkSpeed = UKismetMathLibrary::FInterpTo(GetCharacterMovement()->MaxWalkSpeed, MaxSpeed, DeltaSeconds, 4.0f);
}

void ADaishoProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADaishoProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADaishoProjectCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		bAccelerationFlag = true;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADaishoProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		bAccelerationFlag = true;
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
