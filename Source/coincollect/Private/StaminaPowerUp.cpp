// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaPowerUp.h"
#include "PlayerCharacter.h"

// Sets default values
AStaminaPowerUp::AStaminaPowerUp()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
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
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AStaminaPowerUp::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AStaminaPowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStaminaPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStaminaPowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			// Increase the player's stamina
			PlayerCharacter->Stamina = FMath::Min(PlayerCharacter->Stamina + StaminaIncreaseAmount, PlayerCharacter->MaxStamina);

			// Destroy the power up
			Destroy();
		}
	}
}

