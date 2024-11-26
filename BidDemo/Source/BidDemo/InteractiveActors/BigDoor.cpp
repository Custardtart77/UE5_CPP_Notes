// Fill out your copyright notice in the Description page of Project Settings.


#include "BigDoor.h"

#include "Components/StaticMeshComponent.h"
#include "CubeBlock.h"

// Sets default values
ABigDoor::ABigDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// �����ŵ� Mesh
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

// ����
void ABigDoor::OpenDoor()
{
	// �������ʹ��ƽ�ơ���ת�����ȷ�ʽ������
	UE_LOG(LogTemp, Warning, TEXT("Door is opening..."));
	// �����ͨ���޸��ŵ�λ�û򲥷Ŷ���������
}
