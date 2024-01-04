// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "DoubleCoin.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter() :

    bDead(false),
    Health(100.0f),
    HealingRate(0.5f),
    MaxHealth(100.0f),
    WalkSpeed(300.0f)


{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    mSpringArm->TargetArmLength = 300.0f;
    mSpringArm->SetupAttachment(RootComponent);

    mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
    mCamera->SetupAttachment(mSpringArm, USpringArmComponent::SocketName);

    mCamera->bUsePawnControlRotation = false;
    mSpringArm->bUsePawnControlRotation = true;
    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(CounterTimerHandle, this, &APlayerCharacter::DecrementCounter, 1.0f, true, 0.0f);

}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJumping);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::RunPressed);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::RunReleased);

}

void APlayerCharacter::UpdateMovementParams()
{
    GetCharacterMovement()->MaxWalkSpeed = bRunning && !bStaminaDrained ? RunSpeed : WalkSpeed;
}

void APlayerCharacter::RunPressed()
{
    bRunning = true;
    UpdateMovementParams();
}

void APlayerCharacter::RunReleased()
{
    bRunning = false;
    UpdateMovementParams();
}

void APlayerCharacter::Tick(float DeltaTime)
{


    if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
        if (bRunning && !bStaminaDrained)
        {
            if (!GetCharacterMovement()->Velocity.IsNearlyZero(0.01f))
            {
                Stamina = FMath::Max(0.0f, Stamina - StaminaDrainRate * DeltaTime);
                if (Stamina == 0.0f)
                {
                    bStaminaDrained = true;
                    UpdateMovementParams();
                }
            }
        }
        else
        {
            Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
            if (Stamina >= MaxStamina)
            {
                bStaminaDrained = false;
                UpdateMovementParams();
            }
        }
  /*  GEngine->AddOnScreenDebugMessage(0, DeltaTime, FColor::Red, FString::Printf(TEXT("Stamina %f, Health %f"), Stamina, Health));*/

    if (!bDead)
    {
        Health = FMath::Min(MaxHealth, Health + (HealingRate * DeltaTime));
    }

}

void APlayerCharacter::MoveForward(float value)
{
    FRotator Rotation = GetController()->GetControlRotation();
    FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
    FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(ForwardDirection, value);
}
void APlayerCharacter::MoveRight(float value)
{
    FRotator Rotation = GetController()->GetControlRotation();
    FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
    FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(RightDirection, value);
}



void APlayerCharacter::TakeDamage(float DamageAmount) {
    if (!bDead) {
        // Directly subtract the trap's damage value from Health
        Health -= DamageAmount;

        // Clamp Health between 0.0f and MaxHealth
        Health = FMath::Clamp(Health, 0.0f, MaxHealth);

        // Check for death
        if (Health <= 0.0f) {
            bDead = true;
        }
    }
}
void APlayerCharacter::CollectCoin(ACoin* CollectedCoin)
{
    if (CollectedCoin)
    {
        NumCoinsCollected++;
        UE_LOG(LogTemp, Warning, TEXT("Coin Collected! Total Coins: %d"), NumCoinsCollected);
     
    }
}

void APlayerCharacter::LoseCoin()
{
    if (NumCoinsCollected > 0)
    {
        NumCoinsCollected--;
        UE_LOG(LogTemp, Warning, TEXT("Coin Lost! Total Coins: %d"), NumCoinsCollected);
    }
}

void APlayerCharacter::CollectDoubleCoin(ADoubleCoin* CollectedCoin)
{
    if (CollectedCoin)
    {
        NumCoinsCollected += 2;  // Increase score by 2
        UE_LOG(LogTemp, Warning, TEXT("Double Coin Collected! Total Coins: %d"), NumCoinsCollected);
    }
}

void APlayerCharacter::DecrementCounter()
{
    Counter--;

    if (Counter == 0) {
        // Counter has reached 0, stop the timer
        GetWorldTimerManager().ClearTimer(CounterTimerHandle);

        
        UE_LOG(LogTemp, Warning, TEXT("Counter has reached 0!"));
    }
}
