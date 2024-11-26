// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyActor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

#include "BidDemoCharacter.h"

// Sets default values
AKeyActor::AKeyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �����������
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	RootComponent = KeyMesh;

	// ����������Χ
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetupAttachment(RootComponent);
	TriggerSphere->SetSphereRadius(150.f);

	// ���¼�
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AKeyActor::OnOverlapBegin);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &AKeyActor::OnOverlapEnd);

	bCanPickup = false;
}

// Called when the game starts or when spawned
void AKeyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKeyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		ABidDemoCharacter* Player = Cast<ABidDemoCharacter>(OtherActor);
		if (Player)
		{
			Player->CurrentKey = this; // ������ҵ�ǰ�ɽ�����Կ��
			UE_LOG(LogTemp, Log, TEXT("Player can pick up the key."));
		}
	}
}

void AKeyActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		ABidDemoCharacter* Player = Cast<ABidDemoCharacter>(OtherActor);
		if (Player)
		{
			if (Player->CurrentKey == this)
			{
				Player->CurrentKey = nullptr; // �����ҵ�ǰԿ������
			}
			UE_LOG(LogTemp, Log, TEXT("Player left the key's range."));
		}
	}
}

void AKeyActor::Pickup()
{
	if (bCanPickup)
	{
		UE_LOG(LogTemp, Log, TEXT("Key picked up!"));
		Destroy(); // ����Կ��
	}
}