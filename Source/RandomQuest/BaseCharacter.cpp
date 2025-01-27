// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "BaseCharacter.h"
#include "CharacterObject.h"
#include "WorldDataInstance.h"
#include "ItemInstanceObject.h"
#include "RPGRules.h"
#include "RPGCharacter.h"
#include "RPGSkill.h"
#include "RPGItem.h"
#include "RPGCombatRating.h"
#include "RPGDamageInfo.h"
#include "RPGHealInfo.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsDead())
		return;

	auto worldData = GetWorldData();
	RPGRules* rules = worldData->GetRules();
	ensure(rules);
	rules->UpdateCharacter(DeltaSeconds, &character->character);

	if (!character->character.IsUsingSkill() || IsHoldingSkillTime())
		return;

	activeSkillTime += DeltaSeconds;
	RPGSkill* activeSkill = character->character.GetActiveSkill();
	auto commands = activeSkill->GetCommands();
	TArray<FSkillCommand> toExecute;
	while (activeCommandIndex < commands.Num())
	{
		RPGSkill::Command& cmd = commands[activeCommandIndex];
		if (cmd.time > activeSkillTime)
			break;
		toExecute.Add(FSkillCommand(cmd.command, cmd.param, cmd.time, cmd.value));
		++activeCommandIndex;
	}
	if (toExecute.Num() > 0)
		OnExecuteSkillCommand(toExecute);
	ensure(activeCommandIndex <= commands.Num());
	if (activeCommandIndex == commands.Num())
		character->character.ClearActiveSkill();
}

void ABaseCharacter::Init(UCharacterObject* characterObject)
{
	character = characterObject;
}

bool ABaseCharacter::TryUseSkill(FName name, AActor* target, FName& resourceNeeded)
{
	ensure(!IsDead());
	auto worldData = GetWorldData();
	RPGRules* rules = worldData->GetRules();
	RPGSkill* skill = worldData->GetSkill(name);
	ensure(rules && skill);
	if (!rules->CanUseSkill(&character->character, skill, resourceNeeded))
		return false;
	character->character.SetActiveSkill(skill);
	rules->DeductSkillCost(&character->character, skill);
	activeSkillTime = 0.f;
	activeCommandIndex = 0;
	holdSkillTime = false;
	OnSkillActivated(name, target);
	return true;
}

TArray<FSkill> ABaseCharacter::GetSkills() const
{
	auto worldData = GetWorldData();
	TArray<FSkill> skills;
	auto rpgSkills = character->character.GetSkills();
	for (auto skill : rpgSkills)
		skills.Add(FSkill(skill, worldData));
	
	RPGRules* rules = worldData->GetRules();
	TArray<RPGSkill*> itemSkills;
	for (auto item : GetEquipments())
	{
		auto rpgItem = item->item.GetItem();
		for (auto skill : rpgItem->GetSkills())
		{
			if (itemSkills.Contains(skill))
				continue;
			auto rpgPrerequisite = worldData->GetPrerequisite(skill->GetName());
			if (rpgPrerequisite == nullptr || rules->MeetPrerequisite(&character->character, rpgPrerequisite))
				itemSkills.Add(skill);
		}
	}
	for (auto skill : itemSkills)
		skills.Add(FSkill(skill, worldData));

	return skills;
}

TArray<FTrait> ABaseCharacter::GetTraits() const
{
	auto worldData = GetWorldData();
	TArray<FTrait> traits;
	auto rpgTraits = character->character.GetTraits();
	for (auto trait : rpgTraits)
		traits.Add(FTrait(trait, worldData));
	return traits;
}

int32 ABaseCharacter::GetAttributeValue(FName attribute) const
{
	return character->character.GetAttribute(attribute)->GetValue();
}

int32 ABaseCharacter::GetMaxAttributeValue(FName attribute) const
{
	return character->character.GetAttribute(attribute)->GetMaxValue();
}

int32 ABaseCharacter::GetMinAttributeValue(FName attribute) const
{
	return character->character.GetAttribute(attribute)->GetMinValue();
}

float ABaseCharacter::GetAttributeValueAsPecent(FName attribute) const
{
	return static_cast<float>(GetAttributeValue(attribute)) / static_cast<float>(GetMaxAttributeValue(attribute));
}

bool ABaseCharacter::IsDead() const
{
	auto worldData = GetWorldData();
	RPGRules* rules = worldData->GetRules();
	return rules->IsDead(&character->character);
}

bool ABaseCharacter::IsUsingSkill() const
{
	return character->character.IsUsingSkill();
}

void ABaseCharacter::HoldSkillTime()
{
	holdSkillTime = true;
}

void ABaseCharacter::ResumeSkillTime()
{
	holdSkillTime = false;
}

bool ABaseCharacter::IsHoldingSkillTime() const
{
	return holdSkillTime;
}

void ABaseCharacter::ApplyHealing(ABaseCharacter* healer, int amount, FName healingType)
{
	auto rules = GetWorldData()->GetRules();
	ensure(rules != nullptr);

	FHealInfo healInfo;
	healInfo.healingType = healingType;
	healInfo.amount = rules->ApplyHealing(&healer->character->character, &character->character, amount, healingType, healInfo.isCritical, healInfo.isFumbled);
	OnHealed(healer, healInfo);
}

void ABaseCharacter::ApplyDamage(ABaseCharacter* originator, int amount, FName damageType)
{
	auto world = GetWorldData();
	ensure(world != nullptr);
	auto rules = world->GetRules();
	ensure(rules != nullptr);

	FDamageInfo damageInfo;
	damageInfo.damageType = damageType;
	damageInfo.amount = rules->ApplyDamage(&originator->character->character, &character->character, amount, damageType, damageInfo.isCritical, damageInfo.isFumbled);
	OnDamaged(originator, damageInfo);
	PostDamagedLogic(world);
}

void ABaseCharacter::EquipItem(UItemInstanceObject* item)
{
	ensure(CanEquip(item));
	ensure(!IsEquipped(item));
	character->equipments.Add(item);
	character->freeEquipSlots.Equip(*GetEquipSlot(item));
	OnItemEquipped(item);
}

void ABaseCharacter::RemoveItem(UItemInstanceObject* item)
{
	ensure(IsEquipped(item));
	character->equipments.Remove(item);
	character->freeEquipSlots.Unequip(*GetEquipSlot(item));
	OnItemRemoved(item);
}

bool ABaseCharacter::CanEquip(const UItemInstanceObject* item) const
{
	ensure(item != nullptr && item->item.IsValid());
	FName slotName = item->item.GetEquipSlot();
	if (slotName.IsNone() || !slotName.IsValid())
		return false;
	auto equipSlot = GetEquipSlot(item);
	return equipSlot->IsEquippable() && character->freeEquipSlots.CanEquip(*equipSlot);
}

bool ABaseCharacter::IsEquipped(const UItemInstanceObject* item) const
{
	ensure(item != nullptr && item->item.IsValid());
	return character->equipments.Contains(item);
}

TArray<UItemInstanceObject*>& ABaseCharacter::GetEquipments() const
{
	return character->equipments;
}

void ABaseCharacter::OnHealed_Implementation(ABaseCharacter* healer, const FHealInfo& healInfo)
{
}

void ABaseCharacter::OnDamaged_Implementation(ABaseCharacter* originator, const FDamageInfo& damageInfo)
{
}

void ABaseCharacter::OnSkillActivated_Implementation(FName name, AActor* target)
{
}

void ABaseCharacter::OnExecuteSkillCommand_Implementation(const TArray<FSkillCommand>& commands)
{
	ensure(commands.Num() > 0);
}

void ABaseCharacter::OnItemEquipped_Implementation(UItemInstanceObject* item)
{
	ensure(item != nullptr);
}

void ABaseCharacter::OnItemRemoved_Implementation(UItemInstanceObject* item)
{
	ensure(item != nullptr);
}

UWorldDataInstance* ABaseCharacter::GetWorldData() const
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetGameInstance());
	ensure(wdi != nullptr);
	return wdi;
}

RPGEquipSlot* ABaseCharacter::GetEquipSlot(const UItemInstanceObject* item) const
{
	auto wdi = GetWorldData();
	auto equipSlot = wdi->GetEquipSlot(item->item.GetEquipSlot());
	ensure(equipSlot != nullptr);
	return equipSlot;
}

void ABaseCharacter::PostDamagedLogic(UWorldDataInstance* world)
{
	if (IsDead() && world->party.Contains(character))
	{
		world->party.Remove(character);
		world->killed.Add(character);
	}
}

FDamageInfo::FDamageInfo()
	: amount(0)
	, isCritical(false)
	, isFumbled(false)
{}

FDamageInfo::FDamageInfo(const RPGDamageInfo& damageInfo)
{
	amount = damageInfo.amount;	
	isCritical = damageInfo.isCritical;
	isFumbled = damageInfo.isFumbled;
	damageType = damageInfo.damageType;
}

FHealInfo::FHealInfo()
	: amount(0)
	, isCritical(false)
	, isFumbled(false)
{}

FHealInfo::FHealInfo(const RPGHealInfo& healInfo)
{
	amount = healInfo.amount;
	isCritical = healInfo.isCritical;
	isFumbled = healInfo.isFumbled;
	healingType = healInfo.healingType;
}
