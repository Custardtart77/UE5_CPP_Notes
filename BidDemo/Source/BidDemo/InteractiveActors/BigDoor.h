// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BigDoor.generated.h"

UCLASS()
class BIDDEMO_API ABigDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABigDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// 门的 Mesh 组件
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	// 打开门的函数
	void OpenDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ACubeBlock")
	TArray<class ACubeBlock*> CubeBlockArray;
};
