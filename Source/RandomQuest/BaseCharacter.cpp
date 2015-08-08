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
		RPGSkill::Command& skillCmd = commands[activeCommandIndex];
		if (skillCmd.time > activeSkillTime)
			break;
		FSkillCommand cmd;
		cmd.command = skillCmd.command;
		cmd.time = skillCmd.time;
		cmd.value = skillCmd.value;
		toExecute.Add(cmd);
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

bool ABaseCharacter::TryUseSkill(FName name)
{
	UWorldDataInstance* wdi = Cast<UWorldDataInstance>(GetOwner()->GetGameInstance());
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
