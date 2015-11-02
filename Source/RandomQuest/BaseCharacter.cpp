// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "BaseCharacter.h"
#include "CharacterObject.h"
#include "WorldDataInstance.h"
#include "RPGRules.h"
#include "RPGCharacter.h"
#include "RPGSkill.h"

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
	rules->UpdateCharacter(DeltaSeconds, character->character);

	if (!character->character->IsUsingSkill())
		return;

	activeSkillTime += DeltaSeconds;
	RPGSkill* activeSkill = character->character->GetActiveSkill();
	auto commands = activeSkill->GetCommands();
	TArray<FSkillCommand> toExecute;
	while (activeCommandIndex < commands.Num())
	{
		RPGSkill::Command& cmd = commands[activeCommandIndex];
		if (cmd.time > activeSkillTime)
			break;
		toExecute.Add(FSkillCommand(cmd.command, cmd.time, cmd.value));
		++activeCommandIndex;
	}
	if (toExecute.Num() > 0)
		OnExecuteSkillCommand(toExecute);
	ensure(activeCommandIndex <= commands.Num());
	if (activeCommandIndex == commands.Num())
		character->character->ClearActiveSkill();
}

void ABaseCharacter::Init(UCharacterObject* characterObject)
{
	character = characterObject;
}

bool ABaseCharacter::TryUseSkill(FName name, AActor* target)
{
	ensure(!IsDead());
	auto worldData = GetWorldData();
	RPGRules* rules = worldData->GetRules();
	RPGSkill* skill = worldData->GetSkill(name);
	ensure(rules && skill);
	if (!rules->CanUseSkill(character->character, skill))
		return false;
	character->character->SetActiveSkill(skill);
	rules->DeductSkillCost(character->character, skill);
	activeSkillTime = 0.f;
	activeCommandIndex = 0;
	OnSkillActivated(name, target);
	return true;
}

TArray<FSkill> ABaseCharacter::GetSkills() const
{
	TArray<FSkill> skills;
	auto rpgSkills = character->character->GetSkills();
	for (auto skill : rpgSkills)
		skills.Add(FSkill(skill));
	return skills;
}

TArray<FTrait> ABaseCharacter::GetTraits() const
{
	TArray<FTrait> traits;
	auto rpgTraits = character->character->GetTraits();
	for (auto trait : rpgTraits)
		traits.Add(FTrait(trait));
	return traits;
}

int32 ABaseCharacter::GetAttributeValue(FName attribute) const
{
	return character->character->GetAttribute(attribute)->GetValue();
}

int32 ABaseCharacter::GetMaxAttributeValue(FName attribute) const
{
	return character->character->GetAttribute(attribute)->GetMaxValue();
}

int32 ABaseCharacter::GetMinAttributeValue(FName attribute) const
{
	return character->character->GetAttribute(attribute)->GetMinValue();
}

float ABaseCharacter::GetAttributeValueAsPecent(FName attribute) const
{
	return static_cast<float>(GetAttributeValue(attribute)) / static_cast<float>(GetMaxAttributeValue(attribute));
}

bool ABaseCharacter::IsDead() const
{
	auto worldData = GetWorldData();
	RPGRules* rules = worldData->GetRules();
	return rules->IsDead(character->character);
}

void ABaseCharacter::ApplyHealing(ABaseCharacter* healer, int amount, FName healingType)
{
	auto rules = GetWorldData()->GetRules();
	ensure(rules != nullptr);
	bool isCritical = false;
	int hpHealed = rules->ApplyHealing(healer->character->character, character->character, amount, healingType, isCritical);
	OnHealed(healer, hpHealed, isCritical, healingType);
}

void ABaseCharacter::ApplyDamage(ABaseCharacter* originator, int amount, FName damageType)
{
	auto world = GetWorldData();
	ensure(world != nullptr);
	auto rules = world->GetRules();
	ensure(rules != nullptr);
	bool isCritical = false;
	int hpLost = rules->ApplyDamage(originator->character->character, character->character, amount, damageType, isCritical);
	OnDamaged(originator, hpLost, isCritical, damageType);
	if (IsDead() && world->party.Contains(character))
	{
		world->party.Remove(character);
		world->killed.Add(character);
	}
}

void ABaseCharacter::OnHealed_Implementation(ABaseCharacter* healer, int32 amount, bool isCritical, FName healingType)
{
}

void ABaseCharacter::OnDamaged_Implementation(ABaseCharacter* originator, int32 amount, bool isCritical, FName damageType)
{
}

void ABaseCharacter::OnSkillActivated_Implementation(FName name, AActor* target)
{
}

void ABaseCharacter::OnExecuteSkillCommand_Implementation(const TArray<FSkillCommand>& commands)
{
	ensure(commands.Num() > 0);
}

UWorldDataInstance* ABaseCharacter::GetWorldData() const
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetGameInstance());
	ensure(wdi != nullptr);
	return wdi;
}
