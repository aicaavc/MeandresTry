// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, Category = "Platform")
	float MovementSpeed = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Platform")
	float MovementDistance = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Platform")
	float MinHeight = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Platform")
	float MaxHeight = 200.0f;

	FVector InitialLocation;

	float CurrentPosition = 0.0f;
	float Direction = 1.0f; // 1 for up, -1 for down

};


