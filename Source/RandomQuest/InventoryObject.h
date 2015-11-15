// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "InventoryObject.generated.h"

class RPGInventory;
class RPGItem;


USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName category;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName subtype;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	FName equipSlot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	float size;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	float weight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 protection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool isUnique;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	bool isQuestItem;

	FItem(){}
	FItem(RPGItem* item);
};

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
	void Init();

	UFUNCTION(BlueprintCallable, Category = RPG)
	void AddItem(const FItem& item);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void RemoveItem(const FItem& item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 ItemsCount() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	FItem GetItem(int32 index) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	TArray<FItem> GetItems() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void AddGold(int32 amount);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void SubtractGold(int32 amount);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetGold(int32 amount) const;

private:
	RPGItem* CreateItem(const FItem& item);

	RPGInventory* inventory;
	int32 gold;
};
