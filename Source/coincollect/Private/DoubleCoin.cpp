// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleCoin.h"
#include "PlayerCharacter.h"

// Sets default values
ADoubleCoin::ADoubleCoin()
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
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ADoubleCoin::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ADoubleCoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoubleCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Coin'i Y ekseninde döndür
    FRotator CurrentRotation = MeshComp->GetComponentRotation();
    MeshComp->SetWorldRotation(FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw + DeltaTime * 45.0f, CurrentRotation.Roll)); // 45 derece/saniye hýzýnda döndür

}

void ADoubleCoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA(APlayerCharacter::StaticClass()))
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->CollectDoubleCoin(this);  // Call the modified function
            Destroy();
        }
    }
}

