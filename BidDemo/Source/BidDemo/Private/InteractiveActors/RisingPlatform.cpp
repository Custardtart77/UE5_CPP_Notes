// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActors/RisingPlatform.h"

// Sets default values
ARisingPlatform::ARisingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARisingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARisingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

