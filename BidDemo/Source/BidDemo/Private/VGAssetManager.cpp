// Fill out your copyright notice in the Description page of Project Settings.


#include "VGAssetManager.h"

UVGAssetManager* UVGAssetManager::Get() {

	UVGAssetManager* This = Cast<UVGAssetManager>(GEngine->AssetManager);
	if (This)
	{
		return This;
	}
	else
	{
		return NewObject<UVGAssetManager>(); // never calls this
	}
}

void UVGAssetManager::VGAsyncLoadObject(FString path, FOnPackageLoaded OnPackageLoaded) {
	CurrentLoadPackage = FName(path);

	if (CurrentLoadPackage.IsNone() || CurrentLoadPackage == TEXT("") || CurrentLoadPackage == TEXT("None"))
	{
		// UE_LOG(LogTemp, Warning, TEXT("the map name is blanket, CurrentLoadPackage: %s"), path.GetCharArray());
		//return;
	}
	LoadPackageAsync(
		path,
		FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
			{
				if (Result == EAsyncLoadingResult::Succeeded)
				{
					//可执行通知进行地图切换，即openlevel
					OnPackageLoaded.ExecuteIfBound();
				}
			}), 0, PKG_ContainsMap);
	return;
}

float UVGAssetManager::GetCurrentLoadProgress(FName PackageName, int32& LoadedCount, int32& RequestedCount) const {
	if (PackageName.IsNone() || PackageName == TEXT(""))
	{
		return GetAsyncLoadPercentage(CurrentLoadPackage);
	}
	else
	{
		return GetAsyncLoadPercentage(PackageName);
	}
}