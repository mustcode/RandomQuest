// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "WorldDataInstance.generated.h"

class ULocationObject;

/**
 * 
 */
UCLASS()
class RANDOMQUEST_API UWorldDataInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UWorldDataInstance(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateLocation(FName name, FName type, ULocationObject* parent) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateTown(FName name, FName type, ULocationObject* parent) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateStructure(FName name, FName type, ULocationObject* parent) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateDungeon(FName name, FName type, ULocationObject* parent) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* GetRealmByName(FName name) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* GetTownByName(FName name) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* GetDungeonByName(FName name) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void SetCurrentTown(FName name);

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* GetCurrentTown() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void SetCurrentDungeon(FName name);

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* GetCurrentDungeon() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	uint32 masterSeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	ULocationObject* world;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<ULocationObject*> realms;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<ULocationObject*> towns;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<ULocationObject*> dungeons;

	UPROPERTY(BlueprintReadWrite, Category = RPG)
	FName currentGate;

private:
	ULocationObject* FindLocationByName(TArray<ULocationObject*> locations, const FName& name) const;
	ULocationObject* currentTown;
	ULocationObject* currentDungeon;
};
