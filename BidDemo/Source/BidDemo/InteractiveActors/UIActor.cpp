// Fill out your copyright notice in the Description page of Project Settings.


#include "UIActor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

// Sets default values
AUIActor::AUIActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �����������
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

	// ����������Χ
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(200.f, 100.f, 100.f));

	// ���¼�
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AUIActor::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AUIActor::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AUIActor::BeginPlay()
{
	Super::BeginPlay();
	
    /* Ҳ����ʹ�ü����࣬Ҳ����
    // ʹ�� ConstructorHelpers ������ͼ��
    static ConstructorHelpers::FClassFinder<UUserWidget> InteractionButtonWidgetBP(TEXT("/Game/UI/BP_InteractionButton")); // ��ͼ��·��

    // ȷ���ɹ�������ͼ
    if (InteractionButtonWidgetBP.Succeeded())
    {
        InteractionButtonWidgetClass = InteractionButtonWidgetBP.Class;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find BP_InteractionButton!"));
    }
    */

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
                InteractionButton->OnClicked.AddDynamic(this, &AUIActor::OnInteractionButtonClicked);
            }

            
        }
    }
}

// Called every frame
void AUIActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUIActor::OnInteractionButtonClicked()
{
    GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Yellow, TEXT("Button is clicked!"));

}

// ������ҿ����Ĵ���
void AUIActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    
    InteractionButtonWidget->SetVisibility(ESlateVisibility::Visible);
}

// �뿪��Χ
void AUIActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    InteractionButtonWidget->SetVisibility(ESlateVisibility::Hidden);

}