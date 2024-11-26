// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeBlock.generated.h"

// 声明一个无参数的单点委托类型
DECLARE_DELEGATE(FOnButtonClickedDelegate)

UCLASS()
class BIDDEMO_API ACubeBlock : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ACubeBlock();

	FOnButtonClickedDelegate OnRotationEvent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// 旋转目标角度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	FRotator TargetRotation;

	// 方块的 Mesh 组件
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	// 触发范围
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* TriggerBox;

	// 持有 InteractionButtonWidget 的类
	// 需要在detail面板上选择对应的UI蓝图
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractionButtonWidgetClass;

	// 显示的 UI 按钮
	UUserWidget* InteractionButtonWidget;

	UFUNCTION()
	void OnInteractionButtonClicked();

	// 是否已旋转到正确的目标
	bool bIsCorrectlyRotated;

	// 方块被点击时触发
	// void OnClicked();

		// 处理玩家靠近的触发
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 离开范围
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
