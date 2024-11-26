// Fill out your copyright notice in the Description page of Project Settings.


#include "BigDoor.h"

#include "Components/StaticMeshComponent.h"
#include "CubeBlock.h"

// Sets default values
ABigDoor::ABigDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 创建门的 Mesh
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
}

// Called when the game starts or when spawned
void ABigDoor::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < CubeBlockArray.Num(); i++)
	{
		CubeBlockArray[i]->OnRotationEvent.BindUObject(this, &ABigDoor::OpenDoor);
	}
}

// Called every frame
void ABigDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 打开门
void ABigDoor::OpenDoor()
{
	// 这里可以使用平移、旋转动画等方式来打开门
	UE_LOG(LogTemp, Warning, TEXT("Door is opening..."));
	// 你可以通过修改门的位置或播放动画来打开门
}
