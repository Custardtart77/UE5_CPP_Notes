// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "VGAssetManager.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_DELEGATE(FOnPackageLoaded);

UCLASS()
class BIDDEMO_API UVGAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurrentLoadPackage;

public:
	UFUNCTION(BlueprintPure, CallInEditor, DisplayName = "UVGAssetManager")
	static UVGAssetManager* Get();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void VGAsyncLoadObject(FString path, FOnPackageLoaded OnPackageLoaded);

	UFUNCTION(BlueprintCallable, CallInEditor)
	float GetCurrentLoadProgress(FName PackageName, int32& LoadedCount, int32& RequestedCount) const;
};



