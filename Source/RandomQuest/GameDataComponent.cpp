// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "GameDataComponent.h"
#include "WorldDataInstance.h"
#include "RPGSkill.h"
#include "RPGTrait.h"
#include "RPGOccupation.h"
#include "RPGRace.h"
#include "RPGPrerequisite.h"
#include "RPGItem.h"
#include "RPGEquipSlot.h"


// Sets default values for this component's properties
UGameDataComponent::UGameDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UGameDataComponent::BeginPlay()
{
	Super::BeginPlay();
	wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);

	for (const FSkill& skill : skills)
		AddSkill(skill);
	for (const FTrait& trait : traits)
		AddTrait(trait);

	for (const FSkill& skill : skills)
		AddPrerequisite(skill.name, skill.prerequisite);
	for (const FTrait& trait : traits)
		AddPrerequisite(trait.name, trait.prerequisite);

	for (const FOccupation& occupation : occupations)
		AddOccupation(occupation);
	for (const FRace& race : races)
		AddRace(race);

	for (const FEquipSlot& equipSlot : equipSlots)
		AddEquipSlot(equipSlot);
	for (const FItem& item : items)
		AddItem(item);
}

void UGameDataComponent::AddSkill(const FSkill& skill)
{
	ensure(wdi != nullptr);
	wdi->AddSkill(CreateSkill(skill));
}

void UGameDataComponent::AddTrait(const FTrait& trait)
{
	ensure(wdi != nullptr);
	wdi->AddTrait(CreateTrait(trait));
}

void UGameDataComponent::AddOccupation(const FOccupation& occupation)
{
	ensure(wdi != nullptr);
	wdi->AddOccupation(CreateOccupation(occupation));
}

void UGameDataComponent::AddRace(const FRace& race)
{
	ensure(wdi != nullptr);
	wdi->AddRace(CreateRace(race));
}

void UGameDataComponent::AddEquipSlot(const FEquipSlot& equipSlot)
{
	ensure(wdi != nullptr);
	wdi->AddEquipSlot(CreateEquipSlot(equipSlot));
}

void UGameDataComponent::AddItem(const FItem& item)
{
	ensure(wdi != nullptr);
	wdi->AddItem(CreateItem(item));
}

void UGameDataComponent::AddPrerequisite(FName name, const FPrerequisite& prerequisite)
{
	wdi->AddPrerequisite(CreatePrerequisite(name, prerequisite));
}

RPGSkill* UGameDataComponent::CreateSkill(const FSkill& skill)
{
	RPGSkill* rpgSkill = new RPGSkill(skill.displayName, skill.description, skill.name, skill.variationOf, skill.isUsableInCombat, skill.isUsableOutOfCombat, skill.canSelectTargetAlly, skill.canSelectTargetEnemy);
	for (auto cmd : skill.commands)
		rpgSkill->AddCommand(cmd.command, cmd.time, cmd.value);
	for (auto cost : skill.costs)
		rpgSkill->AddCost(cost.resource, cost.amount);
	return rpgSkill;
}

RPGTrait* UGameDataComponent::CreateTrait(const FTrait& trait)
{
	RPGTrait* rpgTrait = new RPGTrait(trait.displayName, trait.description, trait.name);
	for (auto traitProperty : trait.properties)
		rpgTrait->SetProperty(traitProperty.name, RPGTrait::Property(traitProperty.key, traitProperty.value));
	return rpgTrait;
}

RPGOccupation* UGameDataComponent::CreateOccupation(const FOccupation& occupation)
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);

	RPGOccupation* rpgOccupation = new RPGOccupation(occupation.name);
	for (auto pref : occupation.statPreferences)
		rpgOccupation->SetStatPreference(pref.attribute, pref.weight);
	for (auto trait : occupation.essentialTraits)
		rpgOccupation->AddTrait(wdi->GetTrait(trait), true);
	for (auto trait : occupation.optionalTraits)
		rpgOccupation->AddTrait(wdi->GetTrait(trait), false);
	return rpgOccupation;
}

RPGRace* UGameDataComponent::CreateRace(const FRace& race)
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);

	RPGRace* rpgRace = new RPGRace(race.name);
	for (auto trait : race.traits)
		rpgRace->AddTrait(wdi->GetTrait(trait));
	return rpgRace;
}

RPGPrerequisite* UGameDataComponent::CreatePrerequisite(FName name, const FPrerequisite& prerequisite)
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);

	RPGPrerequisite* rpgPrerequisite = new RPGPrerequisite(name);
	for (auto trait : prerequisite.requiredTraits)
	{
		auto rpgTrait = wdi->GetTrait(trait);
		ensure(rpgTrait != nullptr);
		rpgPrerequisite->RequiredTraits.Add(rpgTrait);
	}
	for (auto trait : prerequisite.bannedTraits)
	{
		auto rpgTrait = wdi->GetTrait(trait);
		ensure(rpgTrait != nullptr);
		rpgPrerequisite->BannedTraits.Add(rpgTrait);
	}
	for (auto requisite : prerequisite.minimumStats)
	{
		TPair<FName, int> item;
		item.Key = requisite.need;
		item.Value = requisite.value;
		rpgPrerequisite->MinimumStats.Add(item);
	}
	return rpgPrerequisite;
}

RPGEquipSlot* UGameDataComponent::CreateEquipSlot(const FEquipSlot& equipSlot)
{
	RPGEquipSlot* rpgEquipSlot = new RPGEquipSlot;
	rpgEquipSlot->Clear();
	rpgEquipSlot->name = equipSlot.name;
	for (auto slot : equipSlot.slots)
	{
		ensure(static_cast<int>(slot.name) < static_cast<int>(RPGEquipSlot::COUNT));
		rpgEquipSlot->slots[static_cast<int>(slot.name)] = slot.count;
	}
	return rpgEquipSlot;
}

RPGItem* UGameDataComponent::CreateItem(const FItem& item)
{
	RPGItem* rpgItem = new RPGItem(item.displayName, item.description, item.name, item.category, item.type, item.subtype, item.equipSlot, item.special, item.size, item.weight, item.damage, item.protection, item.durability, item.value, item.isUnique, item.isQuestItem);

	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
	ensure(wdi != nullptr);
	auto typeTrait = wdi->GetTrait(rpgItem->GetType());
	if (typeTrait != nullptr)
		rpgItem->AddTrait(typeTrait);
	if (rpgItem->GetType() != rpgItem->GetSubType())
	{
		auto subTypeTrait = wdi->GetTrait(rpgItem->GetSubType());
		if (subTypeTrait != nullptr)
			rpgItem->AddTrait(subTypeTrait);
	}
	if (rpgItem->GetName() != rpgItem->GetType() && rpgItem->GetName() != rpgItem->GetSubType())
	{
		auto nameTrait = wdi->GetTrait(rpgItem->GetName());
		if (nameTrait != nullptr)
			rpgItem->AddTrait(nameTrait);
	}
	auto specialTrait = wdi->GetTrait(rpgItem->GetSpecial());
	if (specialTrait != nullptr)
		rpgItem->AddTrait(specialTrait);

	return rpgItem;
}

FSkill::FSkill(RPGSkill* skill, UWorldDataInstance* wdi)
{
	displayName = skill->GetDisplayName();
	description = skill->GetDescription();
	name = skill->GetName();
	variationOf = skill->GetVariationOf();
	isUsableInCombat = skill->IsUsableInCombat();
	isUsableOutOfCombat = skill->IsUsableOutOfCombat();
	canSelectTargetAlly = skill->CanSelectTargetAlly();
	canSelectTargetEnemy = skill->CanSelectTargetEnemy();
	for (auto cmd : skill->GetCommands())
		commands.Add(FSkillCommand(cmd.command, cmd.time, cmd.value));
	for (auto cost : skill->GetCosts())
		costs.Add(FSkillCost(cost.Key, cost.Value));
	ensure(wdi != nullptr);
	wdi->GetPrerequisite(name, prerequisite);
}

FTrait::FTrait(RPGTrait* trait, UWorldDataInstance* wdi)
{
	displayName = trait->GetDisplayName();
	description = trait->GetDescription();
	name = trait->GetName();
	for (auto prop : trait->GetProperties())
		properties.Add(FTraitProperty(prop.Key, prop.Value.key, prop.Value.value));
	ensure(wdi != nullptr);
	wdi->GetPrerequisite(name, prerequisite);
}

FItem::FItem(RPGItem* item)
{
	displayName = item->GetDisplayName();
	description = item->GetDescription();
	name = item->GetName();
	category = item->GetCategory();
	type = item->GetType();
	subtype = item->GetSubType();
	equipSlot = item->GetEquipSlot();
	special = item->GetSpecial();
	size = item->GetSize();
	weight = item->GetWeight();
	damage = item->GetDamage();
	protection = item->GetProtection();
	durability = item->GetDurability();
	value = item->GetValue();
	isUnique = item->IsUnique();
	isQuestItem = item->IsQuestItem();
}
