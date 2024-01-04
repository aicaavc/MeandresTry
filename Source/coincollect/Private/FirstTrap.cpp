// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstTrap.h"
#include "PlayerCharacter.h"

// Sets default values
AFirstTrap::AFirstTrap()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    BoxComponent->SetCollisionProfileName("OverlapAllDynamic");
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFirstTrap::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AFirstTrap::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AFirstTrap::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AFirstTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass()))
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->TakeDamage(13.0f); // Oyuncu karakterine 13 hasar ver
   
        }
    }
}

