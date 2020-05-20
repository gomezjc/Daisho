// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/TimelineComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DaishoProjectCharacter.generated.h"

UCLASS(config=Game)
class ADaishoProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ADaishoProjectCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CurrentSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SpeedWhenStopping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float DashSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsAccelerating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsDashing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bCanDash;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	class UCurveFloat* fCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeDamage;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsComboEnabled;


	UPROPERTY(EditDefaultsOnly, Category = "Melee", meta = (ClampMin = 1.0, UIMin = 1.0))
	float MaxNumComboMultiplier;

	UPROPERTY(EditDefaultsOnly, Category = "Melee", meta = (ClampMin = 1.0, UIMin = 1.0))
	float CurrentComboMultiplier;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* AttackDetectorComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	class UAnimMontage* MeleeMontage;

	class UAnimInstance* AnimInstance;

protected:


	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void Landed(const FHitResult& Hit) override;

	virtual void Jump() override;

	void StartAttack();

	void StopAttack();

	void InitializeReferences();

	UFUNCTION()
	void MakeMeleeDamage(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	// allows to get the Stop Speed and don't override the value when the loop of Tick Continues
	bool bAccelerationFlag;

	FTimerHandle TimerHandle;

	class UTimelineComponent* DashTimeline;

	FOnTimelineFloat InterpolationDash{};

	FOnTimelineEvent DashTimelineFinish{};

	FVector CurrentDashPosition;
	
	FVector DestinationDashPosition;

private:
	// Setter for bAccelerationFlag Variable
	void SetAccelerationFlag(bool Value);

	// Setter for the speed Walk
	void SetWalkSpeed();
	
	void SetRunSpeed();
	
	void SetSprintSpeed();

	void RecoverPlayerMovement();

	void DisablePlayerMovement();

	void Dash();

	void CrouchAction();

	UFUNCTION()
	void TimelineFloatReturn(float value);

	UFUNCTION()
	void OnTimelineFinished();

public:
	void SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState);

	void SetActionState(bool NewState);

	UFUNCTION(BlueprintCallable)
	void SetComboEnabled(bool NewState);

	UFUNCTION(BlueprintCallable)
	void ResetCombo();
};

