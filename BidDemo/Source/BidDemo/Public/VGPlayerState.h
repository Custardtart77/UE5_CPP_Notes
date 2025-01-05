// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "VGPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Health);

/**
 * 
 */
UCLASS()
class BIDDEMO_API AVGPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AVGPlayerState();


	void VGTest();

	FTimerHandle TimerHandle;

	int i = 0;

	// 门的开关状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VGGame")
	float Health = 100;


	// 门的开关状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VGGame")
	float MaxHealth = 100;

	// 委托变量
	UPROPERTY(BlueprintAssignable, Category = "VGGame")
	FOnHealthChanged OnHealthChangedEvent;

	UFUNCTION(BlueprintCallable, Category = "VGGame")
	void SetHealth(float NewHealth);


};
