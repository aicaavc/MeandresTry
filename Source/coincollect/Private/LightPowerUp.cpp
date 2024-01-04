// Fill out your copyright notice in the Description page of Project Settings.


#include "LightPowerUp.h"
#include "PlayerCharacter.h"

// Sets default values
ALightPowerUp::ALightPowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create the point light component.
	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLightComponent"));
	PointLightComponent->SetVisibility(true);

	// Set the point light's properties.
	PointLightComponent->SetLightColor(FColor(255, 0, 0));
	PointLightComponent->SetAttenuationRadius(500.0f);

	// Create a collision box component.
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionBox->SetupAttachment(RootComponent); // Assuming you have a RootComponent in your actor

	// Bind the overlap function to the collision component.
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALightPowerUp::OnOverlapBegin);

}

void ALightPowerUp::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// Check if the other actor is a player character.
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		// Turn off the point light.
		PointLightComponent->SetVisibility(false);
	}
}