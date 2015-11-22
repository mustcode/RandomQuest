// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "InventoryObject.generated.h"

class UItemInstanceObject;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class RANDOMQUEST_API UInventoryObject : public UObject
{
	GENERATED_BODY()
public:
	UInventoryObject();
	~UInventoryObject() override;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void AddItem(UItemInstanceObject* item);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void RemoveItem(UItemInstanceObject* item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool HasItem(UItemInstanceObject* item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	TArray<UItemInstanceObject*>& GetItems();

	UFUNCTION(BlueprintCallable, Category = RPG)
	void AddGold(int32 amount);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void SubtractGold(int32 amount);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetGold(int32 amount) const;

private:
	TArray<UItemInstanceObject*> items;
	int32 gold;
	int32 maxSpace;
	int32 maxWeight;
};
