// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "RPGRules.h"
#include "WorldDataInstance.generated.h"

class ULocationObject;
class UCharacterObject;
class RPGSkill;
class RPGTrait;
class RPGOccupation;
class RPGRace;

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
	ULocationObject* CreateLocation(FName name, FName type, ULocationObject* parent) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateTown(FName name, FName type, ULocationObject* parent) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateStructure(FName name, FName type, ULocationObject* parent) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	ULocationObject* CreateDungeon(FName name, FName type, ULocationObject* parent) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	UCharacterObject* CreateCharacter();

	UFUNCTION(BlueprintCallable, Category = RPG)
	void AddCharacterToParty(UCharacterObject* character);

	UFUNCTION(BlueprintCallable, Category = RPG)
	UCharacterObject* GetCharacterByIndex(int32 index) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	int32 GetCharacterIndex(UCharacterObject* character);

	UFUNCTION(BlueprintCallable, Category = RPG)
	int32 GetPartySize() const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void AddConsequence(FName name);

	UFUNCTION(BlueprintCallable, Category = RPG)
	void RemoveConsequence(FName name);

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool HasConsequence(FName name) const;

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool AbilityTest(FName name, int32 difficulty, int32& result);

	void AddSkill(RPGSkill* skill);
	void AddTrait(RPGTrait* trait);
	void AddOccupation(RPGOccupation* occupation);
	void AddRace(RPGRace* race);

	RPGSkill* GetSkill(FName name) const;
	RPGTrait* GetTrait(FName name) const;
	RPGOccupation* GetOccupation(FName name) const;
	RPGRace* GetRace(FName name) const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	int32 masterSeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = RPG)
	TArray<UCharacterObject*> party;

	UPROPERTY(BlueprintReadWrite, Category = RPG)
	FName currentGate;

private:
	TMap<FName, int32> consequences;
	TMap<FName, RPGSkill*> skills;
	TMap<FName, RPGTrait*> traits;
	TMap<FName, RPGOccupation*> occupations;
	TMap<FName, RPGRace*> races;

	RPGRules rules;
	int gold, silver, copper;
};
