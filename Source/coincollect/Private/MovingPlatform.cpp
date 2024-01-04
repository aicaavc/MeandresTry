// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the default cube mesh component
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube")).Object);
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlatformMesh->SetGenerateOverlapEvents(true);
	RootComponent = PlatformMesh;

	// Set initial location
	InitialLocation = GetActorLocation();

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Set initial position
	CurrentPosition = GetActorLocation().Z;
}
	


// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{

	
	CurrentPosition += Direction * MovementSpeed * DeltaTime;

	// Change direction when reaching movement limits
	if (CurrentPosition >= MaxHeight)
	{
		Direction = -1.0f;
	}
	else if (CurrentPosition <= MinHeight)
	{
		Direction = 1.0f;
	}

	
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, CurrentPosition));

	
	if (CurrentPosition < InitialLocation.Z)
	{
		CurrentPosition = InitialLocation.Z;
	}

}

