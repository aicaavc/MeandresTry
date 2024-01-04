#include "Coin.h"
#include "PlayerCharacter.h"

// Sets default values
ACoin::ACoin()
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
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
}

void ACoin::BeginPlay()
{
    Super::BeginPlay();
}

void ACoin::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Coin'i Y ekseninde döndür
    FRotator CurrentRotation = MeshComp->GetComponentRotation();
    MeshComp->SetWorldRotation(FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw + DeltaTime * 45.0f, CurrentRotation.Roll)); // 45 derece/saniye hýzýnda döndür
}

void ACoin::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (OtherActor->IsA(APlayerCharacter::StaticClass()))
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
        if (PlayerCharacter)
        {
            PlayerCharacter->CollectCoin(this);
            Destroy();
        }
    }
}