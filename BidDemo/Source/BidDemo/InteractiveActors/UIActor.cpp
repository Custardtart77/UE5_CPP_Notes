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

	// 创建网格组件
    TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestMesh"));
	RootComponent = TestMesh;

	// 创建触发范围
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(200.f, 100.f, 100.f));

	// 绑定事件
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AUIActor::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AUIActor::OnOverlapEnd);

    UStaticMesh* StaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));
    if (StaticMesh)
    {
        TestMesh->SetStaticMesh(StaticMesh);
    }
    // UMaterialInstance* CorrectCubeMaterialInstance = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));
    // UMaterial* CorrectCubeMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/StarterContent/Materials/M_Basic_Floor"));
    // UMaterial* CorrectCubeMaterial = FindObject<UMaterial>(nullptr, TEXT("/Game/StarterContent/Materials/M_Basic_Floor"));
    // UMaterial* CorrectCubeMaterial = FindObject<UMaterial>(nullptr, TEXT("/Game/StarterContent/Materials/M_Basic_Floor"));
    /*
    UMaterial* CorrectCubeMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/NewMaterial"));

    if (CorrectCubeMaterial)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Hello");
        TestMesh->SetMaterial(0, CorrectCubeMaterial);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Fail");
    }*/
    // StaticLoadObject
    // FindObject
}
       

// Called when the game starts or when spawned
void AUIActor::BeginPlay()
{
	Super::BeginPlay();
	
    /* 也可以使用加载类，也可以
    // 使用 ConstructorHelpers 加载蓝图类
    static ConstructorHelpers::FClassFinder<UUserWidget> InteractionButtonWidgetBP(TEXT("/Game/UI/BP_InteractionButton")); // 蓝图的路径

    // 确保成功加载蓝图
    if (InteractionButtonWidgetBP.Succeeded())
    {
        InteractionButtonWidgetClass = InteractionButtonWidgetBP.Class;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find BP_InteractionButton!"));
    }
    */

    // 确保我们有正确的 Widget 蓝图
    if (InteractionButtonWidgetClass)
    {
        // 创建按钮 Widget
        // 也可以直接传进控件BP进InteractionButtonWidget，也可以直接根据蓝图路径代码创建Widget，再通过反射的方法FindByName，这样就不用传进类再创建了
        InteractionButtonWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionButtonWidgetClass);

        if (InteractionButtonWidget)
        {
            // 将 Widget 添加到视口
            // InteractionButtonWidget->AddToViewport();

            // 初始隐藏按钮
            // InteractionButtonWidget->SetVisibility(ESlateVisibility::Hidden);

            // 获取按钮组件并绑定事件
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

// 处理玩家靠近的触发
void AUIActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    
    // InteractionButtonWidget->SetVisibility(ESlateVisibility::Visible);
    if (InteractionButtonWidget)
    {
        InteractionButtonWidget->AddToViewport();
    }
}

// 离开范围
void AUIActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // InteractionButtonWidget->SetVisibility(ESlateVisibility::Hidden);
    if (InteractionButtonWidget)
    {
        InteractionButtonWidget->RemoveFromParent();
    }
    
}