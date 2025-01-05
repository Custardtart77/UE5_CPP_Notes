// Fill out your copyright notice in the Description page of Project Settings.


#include "VGPlayerState.h"
#include "TimerManager.h"

AVGPlayerState::AVGPlayerState()
{
	
}





void AVGPlayerState::SetHealth(float NewHealth)
{
	Health = NewHealth;
	OnHealthChangedEvent.Broadcast(Health);
}

void AVGPlayerState::VGTest()
{
	i++;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("ZCT Test %d"), i));



}
