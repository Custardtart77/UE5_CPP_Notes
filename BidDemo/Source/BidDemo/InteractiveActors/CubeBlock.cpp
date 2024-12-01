// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeBlock.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

// Sets default values
ACubeBlock::ACubeBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��������� Mesh
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;

	// ����������Χ
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	// ���¼�
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACubeBlock::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACubeBlock::OnOverlapEnd);

	bIsCorrectlyRotated = false; // Ĭ��û����ת����ȷ��λ��
}

// Called when the game starts or when spawned
void ACubeBlock::BeginPlay()
{
	Super::BeginPlay();
	// �������ó�ʼ��ת
	SetActorRotation(FRotator(0, 0, 0));
	

    // ȷ����������ȷ�� Widget ��ͼ
    if (InteractionButtonWidgetClass)
    {
        // ������ť Widget
        InteractionButtonWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionButtonWidgetClass);

        if (InteractionButtonWidget)
        {
            // �� Widget ��ӵ��ӿ�
            InteractionButtonWidget->AddToViewport();

            // ��ʼ���ذ�ť
            InteractionButtonWidget->SetVisibility(ESlateVisibility::Hidden);

            // ��ȡ��ť��������¼�
            UButton* InteractionButton = Cast<UButton>(InteractionButtonWidget->GetWidgetFromName(TEXT("InteractionButton")));
            if (InteractionButton)
            {
                InteractionButton->OnClicked.AddDynamic(this, &ACubeBlock::OnInteractionButtonClicked);
            }


        }
    }
}

// Called every frame
void ACubeBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// �������ʱ���øú���
void ACubeBlock::OnInteractionButtonClicked()
{
    // ������ת��Ŀ��Ƕ�
    SetActorRotation(TargetRotation);

    // ��鷽���Ƿ�����ת����ȷλ��
    if (GetActorRotation().Equals(TargetRotation, 1.0f))  // ��ת�Ƿ��Ѿ��ﵽĿ��
    {
        bIsCorrectlyRotated = true;
        UE_LOG(LogTemp, Warning, TEXT("Cube rotated to correct position!"));

        // ���ί���Ƿ���˺���
        if (OnRotationEvent.IsBound())
        {
            OnRotationEvent.Execute(); // ����ί��
        }
        CubeMesh->SetMaterial(0, CorrectCubeMaterial);
    }
    else
    {
        bIsCorrectlyRotated = false;
    }

    static ConstructorHelpers::FObjectFinder<UMaterialInstance> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/ASSA"));
    if (CubeVisualAsset.Succeeded())
    {
        CorrectCubeMaterial = CubeVisualAsset.Object;
    }
    CubeMesh->SetMaterial(0, CorrectCubeMaterial);
}


// ������ҿ����Ĵ���
void ACubeBlock::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    InteractionButtonWidget->SetVisibility(ESlateVisibility::Visible);
}

// �뿪��Χ
void ACubeBlock::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    InteractionButtonWidget->SetVisibility(ESlateVisibility::Hidden);

}
