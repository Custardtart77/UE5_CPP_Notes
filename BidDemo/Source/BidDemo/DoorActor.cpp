// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

#include "BidDemoCharacter.h"

#include "ALSV4_CPP/Public/Character/ALSCharacter.h"

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建网格组件
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

	// 创建触发范围
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(200.f, 100.f, 100.f));

	// 绑定事件
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADoorActor::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADoorActor::OnOverlapEnd);

	bIsOpen = false;
	bPlayerHasKey = false;
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 开门逻辑（平滑开门）
	if (bIsOpen)
	{
		FRotator CurrentRotation = DoorMesh->GetRelativeRotation();
		FRotator TargetRotation = FRotator(0.f, 90.f, 0.f); // 假设开门旋转90度
		DoorMesh->SetRelativeRotation(FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 2.f));
	}
}

void ADoorActor::OpenDoor()
{
	if (bPlayerHasKey)
	{
		bIsOpen = true;
		UE_LOG(LogTemp, Log, TEXT("Door is opening!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Door is locked! You need a key."));
	}
}

void ADoorActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		ABidDemoCharacter* Player = Cast<ABidDemoCharacter>(OtherActor);
		if (Player)
		{
			Player->CurrentDoor = this; // 设置玩家当前可交互的门
			UE_LOG(LogTemp, Log, TEXT("Player can use the door."));
		}
	}
}

void ADoorActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		ABidDemoCharacter* Player = Cast<ABidDemoCharacter>(OtherActor);
		if (Player)
		{
			if (Player->CurrentDoor == this)
			{
				Player->CurrentDoor = nullptr; // 清除玩家当前门引用
			}
			UE_LOG(LogTemp, Log, TEXT("Player left the door's range."));
		}
	}
}