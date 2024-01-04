// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPowerUp.h"
#include "PlayerCharacter.h"

// Sets default values
AHealthPowerUp::AHealthPowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
    if (CubeMeshAsset.Succeeded())
    {
        MeshComp->SetStaticMesh(CubeMeshAsset.Object);
    }

    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
    CollisionComp->SetupAttachment(RootComponent);
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHealthPowerUp::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AHealthPowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}


void AHealthPowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA(APlayerCharacter::StaticClass()))
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            // Oyuncunun canýný artýr
            PlayerCharacter->Health += HealthIncreaseAmount;

            // Canýn 100'den fazla olmasýný engelle
            PlayerCharacter->Health = FMath::Min(PlayerCharacter->Health, PlayerCharacter->MaxHealth);

            // Power up'ý yok et
            Destroy();
        }
    }
}
