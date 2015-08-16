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

TArray<FSkill> ABaseCharacter::GetSkills() const
{
	TArray<FSkill> skills;
	auto rpgSkills = character->character->GetSkills();
	for (auto skill : rpgSkills)
		skills.Add(FSkill(skill));
	return skills;
}

bool ABaseCharacter::TryUseSkill(FName name)
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetGameInstance());
	ensure(wdi != nullptr);
	RPGRules* rules = wdi->GetRules();
	RPGSkill* skill = wdi->GetSkill(name);
	if (!rules->CanUseSkill(character->character, skill))
		return false;
	character->character->SetActiveSkill(skill);
	rules->DeductSkillCost(character->character, skill);
	activeSkillTime = 0.f;
	activeCommandIndex = 0;
	return true;
}

void ABaseCharacter::OnExecuteSkillCommand_Implementation(const TArray<FSkillCommand>& commands)
{
	ensure(commands.Num() > 0);
}
