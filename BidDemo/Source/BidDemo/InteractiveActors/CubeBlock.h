// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeBlock.generated.h"

// ����һ���޲����ĵ���ί������
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


	// ��תĿ��Ƕ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	FRotator TargetRotation;

	// ����� Mesh ���
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	// ������Χ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* TriggerBox;

	// ���� InteractionButtonWidget ����
	// ��Ҫ��detail�����ѡ���Ӧ��UI��ͼ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractionButtonWidgetClass;

	// ��ʾ�� UI ��ť
	UUserWidget* InteractionButtonWidget;

	UFUNCTION()
	void OnInteractionButtonClicked();

	// �Ƿ�����ת����ȷ��Ŀ��
	bool bIsCorrectlyRotated;

	// ���鱻���ʱ����
	// void OnClicked();

		// ������ҿ����Ĵ���
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// �뿪��Χ
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
