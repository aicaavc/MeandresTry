// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Char")
	UCameraComponent* mCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Char")
	USpringArmComponent* mSpringArm;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Char")
	float RunSpeed = 800.0f;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Char")
	float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Char")
	float MaxStamina = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Char")
	float StaminaGainRate = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Char")
	float StaminaDrainRate = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Char")
	bool bStaminaDrained = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Char")
	bool bRunning = false;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Char")
	bool bDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Char")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Char")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Char")
	float HealingRate;
	UPROPERTY(EditAnywhere, Category = "Char")
	float WalkSpeed;
	UFUNCTION(BlueprintCallable, Category = "Char")
	void TakeDamage(float DamageAmount);


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Char")
	int32 Counter = 120;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Char")
	int32 NumCoinsCollected = 0;
	UFUNCTION()
	void CollectCoin(ACoin* CollectedCoin);
	UFUNCTION()
	void LoseCoin();
	UFUNCTION()
	void CollectDoubleCoin(ADoubleCoin* CollectedCoin);




	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void UpdateMovementParams();
	void MoveForward(float value);
	void MoveRight(float value);
	void RunPressed();
	void RunReleased();

	FTimerHandle CounterTimerHandle;
	void DecrementCounter();
};