// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "WorldDataInstance.h"
#include "LocationObject.h"
#include "CharacterObject.h"
#include "ItemInstanceObject.h"
#include "InventoryObject.h"
#include "RPGLocation.h"
#include "RPGTown.h"
#include "RPGStructure.h"
#include "RPGDungeon.h"
#include "RPGCharacter.h"
#include "RPGSkill.h"
#include "RPGTrait.h"
#include "RPGOccupation.h"
#include "RPGRace.h"
#include "RPGPrerequisite.h"
#include "RPGEquipSlot.h"
#include "RPGItem.h"

//#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, text)

UWorldDataInstance::UWorldDataInstance(const FObjectInitializer& ObjectInitializer) 
	: masterSeed(0)
	, inventory(nullptr)
	, Super(ObjectInitializer)
{
}

void UWorldDataInstance::Shutdown()
{
	for (auto skill : skills)
		delete skill;
	for (auto trait : traits)
		delete trait;
	for (auto occupation : occupations)
		delete occupation;
	for (auto race : races)
		delete race;
	for (auto prerequisite : prerequisites)
		delete prerequisite;
	UGameInstance::Shutdown();
}

ULocationObject* UWorldDataInstance::CreateLocation(FName name, FName type, ULocationObject* parent)
{
	ensure(!name.ToString().IsEmpty() && !type.ToString().IsEmpty());
	ULocationObject* locObj = NewObject<ULocationObject>();
	locObj->Init<RPGLocation>(name, type, parent);
	return locObj;
}

ULocationObject* UWorldDataInstance::CreateTown(FName name, FName type, ULocationObject* parent)
{
	ensure(!name.ToString().IsEmpty() && !type.ToString().IsEmpty());
	ULocationObject* locObj = NewObject<ULocationObject>();
	locObj->Init<RPGTown>(name, type, parent);
	return locObj;
}

ULocationObject* UWorldDataInstance::CreateStructure(FName name, FName type, ULocationObject* parent)
{
	ensure(!name.ToString().IsEmpty() && !type.ToString().IsEmpty());
	ULocationObject* locObj = NewObject<ULocationObject>();
	locObj->Init<RPGStructure>(name, type, parent);
	return locObj;
}

ULocationObject* UWorldDataInstance::CreateDungeon(FName name, FName type, ULocationObject* parent)
{
	ensure(!name.ToString().IsEmpty() && !type.ToString().IsEmpty());
	ULocationObject* locObj = NewObject<ULocationObject>();
	locObj->Init<RPGDungeon>(name, type, parent);
	return locObj;
}

UCharacterObject* UWorldDataInstance::CreateCharacter()
{
	UCharacterObject* charObj = NewObject<UCharacterObject>();
	RPGCharacter* character = &charObj->character;
	rules.RandomizeStats(character);
	if (races.Num() > 0)
		rules.AssignRace(character, races);
	rules.RandomizeCommonTraits(character, traits);
	if (occupations.Num() > 0)
		rules.AssignOccupation(character, occupations, prerequisites);
	rules.SetDefaultFreeEquipSlot(&charObj->freeEquipSlots);
	return charObj;
}

UInventoryObject* UWorldDataInstance::CreateInventory(FName name, float maxSpace, float maxWeight)
{
	ensure(!name.IsNone() && name.IsValid());
	ensure(maxSpace > 0 && maxWeight > 0);
	UInventoryObject* inventoryObj = NewObject<UInventoryObject>();
	inventoryObj->SetName(name);
	inventoryObj->SetCapacity(maxSpace, maxWeight);
	return inventoryObj;
}

UInventoryObject* UWorldDataInstance::CreateStorageInventory(FName name, float maxSpace, float maxWeight)
{
	ensure(GetStorageInventory(name) == nullptr);
	auto storageInventory = CreateInventory(name, maxSpace, maxWeight);
	storageInventories.Add(storageInventory);
	return storageInventory;
}

UItemInstanceObject* UWorldDataInstance::CreateItem(FName name)
{
	UItemInstanceObject* item = NewObject<UItemInstanceObject>();
	RPGItem* rpgItem = GetItem(name);
	ensure(rpgItem != nullptr);
	item->item.SetItem(rpgItem);
	return item;
}

void UWorldDataInstance::AddCharacterToParty(UCharacterObject* character)
{
	ensure(character);
	party.Add(character);
}

UCharacterObject* UWorldDataInstance::GetCharacterByIndex(int32 index) const
{
	ensure(index >= 0 && index < party.Num());
	return party[index];
}

int32 UWorldDataInstance::GetCharacterIndex(UCharacterObject* character)
{
	for (int i = 0; i < party.Num(); ++i)
	{
		if (character == party[i])
			return i;
	}
	ensure(false);
	return -1;
}

int32 UWorldDataInstance::GetPartySize() const
{
	return party.Num();
}

void UWorldDataInstance::AddConsequence(FName name)
{
	consequences.Add(name, 1);
}

void UWorldDataInstance::RemoveConsequence(FName name)
{
	consequences.Remove(name);
}

bool UWorldDataInstance::HasConsequence(FName name) const
{
	return consequences.Find(name) != nullptr;
}

bool UWorldDataInstance::AbilityTest(int32 characterIndex, FName attribute, int32 difficulty, int32& result)
{
	ensure(characterIndex < party.Num());
	RPGCharacter* chosen = &party[characterIndex]->character;
	ensure(chosen != nullptr);
	return rules.AbilityTest(chosen, attribute, difficulty, result);
}

TArray<FName> UWorldDataInstance::GetPrimaryStats() const
{
	return rules.GetPrimaryStats();
}

int32 UWorldDataInstance::GetVariableStats(FName& stat1, FName& stat2, FName& stat3, FName& stat4, FName& stat5) const
{
	return rules.GetVariableStats(stat1, stat2, stat3, stat4, stat5);
}

void UWorldDataInstance::GetPrerequisite(FName name, FPrerequisite& prerequisite) const
{
	auto rpgPrerequisite = GetPrerequisite(name);
	if(rpgPrerequisite == nullptr)
		return;
	for (auto requiredTrait : rpgPrerequisite->RequiredTraits)
		prerequisite.requiredTraits.Add(requiredTrait->GetName());
	for (auto bannedTrait : rpgPrerequisite->BannedTraits)
		prerequisite.bannedTraits.Add(bannedTrait->GetName());
	for (auto minStat : rpgPrerequisite->MinimumStats)
		prerequisite.minimumStats.Add(FRequisite(minStat.Key, minStat.Value));
}

void UWorldDataInstance::GetItemFromName(FName name, FItem& item) const
{
	ensure(!name.IsNone() && name.IsValid());
	RPGItem* rpgItem = GetItem(name);
	item = FItem(rpgItem);
}

UInventoryObject* UWorldDataInstance::GetStorageInventory(FName name) const
{
	auto result = storageInventories.FindByPredicate([&](UInventoryObject* inventoryObj) { return inventoryObj->GetName() == name; });
	return (result != nullptr) ? *result : nullptr;
}

void UWorldDataInstance::AddSkill(RPGSkill* skill)
{
	ensure(skill && !skill->GetName().IsNone() && skill->GetName().IsValid());
	ensure(!skills.Contains(skill) && !GetSkill(skill->GetName()));
	skills.Add(skill);
}

void UWorldDataInstance::AddTrait(RPGTrait* trait)
{
	ensure(trait && !trait->GetName().IsNone() && trait->GetName().IsValid());
	ensure(!traits.Contains(trait) && !GetTrait(trait->GetName()));
	traits.Add(trait);
}

void UWorldDataInstance::AddOccupation(RPGOccupation* occupation)
{
	ensure(occupation && !occupation->GetName().IsNone() && occupation->GetName().IsValid());
	ensure(!occupations.Contains(occupation) && !GetOccupation(occupation->GetName()));
	occupations.Add(occupation);
}

void UWorldDataInstance::AddRace(RPGRace* race)
{
	ensure(race && !race->GetName().IsNone() && race->GetName().IsValid());
	ensure(!races.Contains(race) && !GetRace(race->GetName()));
	races.Add(race);
}

void UWorldDataInstance::AddPrerequisite(RPGPrerequisite* prerequisite)
{
	ensure(prerequisite && !prerequisite->GetName().IsNone() && prerequisite->GetName().IsValid());
	ensure(!prerequisites.Contains(prerequisite) && !GetPrerequisite(prerequisite->GetName()));
	prerequisites.Add(prerequisite);
}

void UWorldDataInstance::AddEquipSlot(RPGEquipSlot* equipSlot)
{
	ensure(equipSlot && !equipSlot->name.IsNone() && equipSlot->name.IsValid());
	ensure(!equipSlots.Contains(equipSlot) && !GetEquipSlot(equipSlot->name));
	equipSlots.Add(equipSlot);
}

void UWorldDataInstance::AddItem(RPGItem* item)
{
	ensure(item && !item->GetName().IsNone() && item->GetName().IsValid());
	ensure(!items.Contains(item) && !GetItem(item->GetName()));
	items.Add(item);
}

RPGSkill* UWorldDataInstance::GetSkill(FName name) const
{
	auto result = skills.FindByPredicate([&](RPGSkill* skill){ return skill->GetName() == name; });
	return (result != nullptr) ? *result : nullptr;
}

RPGTrait* UWorldDataInstance::GetTrait(FName name) const
{
	auto result = traits.FindByPredicate([&](RPGTrait* trait){ return trait->GetName() == name; });
	return (result != nullptr) ? *result : nullptr;
}

RPGOccupation* UWorldDataInstance::GetOccupation(FName name) const
{
	auto result = occupations.FindByPredicate([&](RPGOccupation* occupation){ return occupation->GetName() == name; });
	return (result != nullptr) ? *result : nullptr;
}

RPGRace* UWorldDataInstance::GetRace(FName name) const
{
	auto result = races.FindByPredicate([&](RPGRace* race){ return race->GetName() == name; });
	return (result != nullptr) ? *result : nullptr;
}

RPGPrerequisite* UWorldDataInstance::GetPrerequisite(FName name) const
{
	auto result = prerequisites.FindByPredicate([&](RPGPrerequisite* prerequisite){ return prerequisite->GetName() == name; });
	return (result != nullptr) ? *result : nullptr;
}

RPGEquipSlot* UWorldDataInstance::GetEquipSlot(FName name) const
{
	auto result = equipSlots.FindByPredicate([&](RPGEquipSlot* equipSlot) { return equipSlot->name == name; });
	return (result != nullptr) ? *result : nullptr;
}

RPGItem* UWorldDataInstance::GetItem(FName name) const
{
	auto result = items.FindByPredicate([&](RPGItem* item) { return item->GetName() == name; });
	return (result != nullptr) ? *result : nullptr;
}

RPGRules* UWorldDataInstance::GetRules()
{
	return &rules;
}
