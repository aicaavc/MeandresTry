// Fill out your copyright notice in the Description page of Project Settings.


#include "SecondTrap.h"
#include "PlayerCharacter.h"

// Sets default values
ASecondTrap::ASecondTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    BoxComponent->SetCollisionProfileName("OverlapAllDynamic");
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASecondTrap::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ASecondTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASecondTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASecondTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass()))
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->TakeDamage(23.0f); // Oyuncu karakterine 23 hasar ver
            PlayerCharacter->LoseCoin(); // Decrement coins
        }
    }
}

