// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "RPGRules.h"
#include "GameDataComponent.h"
#include "WorldDataInstance.generated.h"

class ULocationObject;
class UCharacterObject;
class UInventoryObject;
class RPGSkill;
class RPGTrait;
class RPGOccupation;
class RPGRace;
class RPGPrerequisite;

/**
 * 
 */
UCLASS()
class RANDOMQUEST_API UWorldDataInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UWorldDataInstance(const FObjectInitializer& ObjectInitializer);
	
	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateLocation(FName name, FName type, ULocationObject* parent);

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateTown(FName name, FName type, ULocationObject* parent);

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateStructure(FName name, FName type, ULocationObject* parent);

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateDungeon(FName name, FName type, ULocationObject* parent);

	UFUNCTION(BlueprintCallable, Category = RPG)
	UCharacterObject* CreateCharacter();

	UFUNCTION(BlueprintCallable, Category = RPG)
	UInventoryObject* CreateInventory(FName name, float maxSpace, float maxWeight);

	UFUNCTION(BlueprintCallable, Category = RPG)
	UInventoryObject* CreateStorageInventory(FName name, float maxSpace, float maxWeight);

	UFUNCTION(BlueprintCallable, Category = RPG)
	UItemInstanceObject* CreateItem(FName name);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void AddCharacterToParty(UCharacterObject* character);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	UCharacterObject* GetCharacterByIndex(int32 index) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	int32 GetCharacterIndex(UCharacterObject* character);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetPartySize() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void AddConsequence(FName name);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void RemoveConsequence(FName name);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	bool HasConsequence(FName name) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool AbilityTest(int32 characterIndex, FName attribute, int32 difficulty, int32& result);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	TArray<FName> GetPrimaryStats() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	int32 GetVariableStats(FName& stat1, FName& stat2, FName& stat3, FName& stat4, FName& stat5) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	void GetPrerequisite(FName name, FPrerequisite& prerequisite) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	void GetItemFromInstance(const UItemInstanceObject* itemInstance, FItem& item) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = RPG)
	UInventoryObject* GetStorageInventory(FName name) const;

	void AddSkill(RPGSkill* skill);
	void AddTrait(RPGTrait* trait);
	void AddOccupation(RPGOccupation* occupation);
	void AddRace(RPGRace* race);
	void AddPrerequisite(RPGPrerequisite* prerequisite);
	void AddEquipSlot(RPGEquipSlot* equipSlot);
	void AddItem(RPGItem* item);

	RPGSkill* GetSkill(FName name) const;
	RPGTrait* GetTrait(FName name) const;
	RPGOccupation* GetOccupation(FName name) const;
	RPGRace* GetRace(FName name) const;
	RPGPrerequisite* GetPrerequisite(FName name) const;
	RPGEquipSlot* GetEquipSlot(FName name) const;
	RPGItem* GetItem(FName name) const;
	RPGRules* GetRules();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 masterSeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<UCharacterObject*> party;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<UCharacterObject*> killed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<UInventoryObject*> storageInventories;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	UInventoryObject* inventory;

	UPROPERTY(BlueprintReadWrite, Category = RPG)
	FName currentGate;

private:
	TMap<FName, int32> consequences;

	TArray<RPGSkill*> skills;
	TArray<RPGTrait*> traits;
	TArray<RPGOccupation*> occupations;
	TArray<RPGRace*> races;
	TArray<RPGPrerequisite*> prerequisites;
	TArray<RPGEquipSlot*> equipSlots;
	TArray<RPGItem*> items;

	RPGRules rules;
};
