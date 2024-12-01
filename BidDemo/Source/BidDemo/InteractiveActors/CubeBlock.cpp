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

	// 创建方块的 Mesh
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	RootComponent = CubeMesh;

	// 创建触发范围
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	// 绑定事件
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACubeBlock::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACubeBlock::OnOverlapEnd);

	bIsCorrectlyRotated = false; // 默认没有旋转到正确的位置
}

// Called when the game starts or when spawned
void ACubeBlock::BeginPlay()
{
	Super::BeginPlay();
	// 可以设置初始旋转
	SetActorRotation(FRotator(0, 0, 0));
	

    // 确保我们有正确的 Widget 蓝图
    if (InteractionButtonWidgetClass)
    {
        // 创建按钮 Widget
        InteractionButtonWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionButtonWidgetClass);

        if (InteractionButtonWidget)
        {
            // 将 Widget 添加到视口
            InteractionButtonWidget->AddToViewport();

            // 初始隐藏按钮
            InteractionButtonWidget->SetVisibility(ESlateVisibility::Hidden);

            // 获取按钮组件并绑定事件
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

// 点击方块时调用该函数
void ACubeBlock::OnInteractionButtonClicked()
{
    // 触发旋转到目标角度
    SetActorRotation(TargetRotation);

    // 检查方块是否已旋转到正确位置
    if (GetActorRotation().Equals(TargetRotation, 1.0f))  // 旋转是否已经达到目标
    {
        bIsCorrectlyRotated = true;
        UE_LOG(LogTemp, Warning, TEXT("Cube rotated to correct position!"));

        // 检查委托是否绑定了函数
        if (OnRotationEvent.IsBound())
        {
            OnRotationEvent.Execute(); // 触发委托
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


// 处理玩家靠近的触发
void ACubeBlock::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    InteractionButtonWidget->SetVisibility(ESlateVisibility::Visible);
}

// 离开范围
void ACubeBlock::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    InteractionButtonWidget->SetVisibility(ESlateVisibility::Hidden);

}
