// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGSkill.h"

RPGSkill::RPGSkill()
{
}

RPGSkill::~RPGSkill()
{
}

void RPGSkill::AddCommand(FName command, float value)
{
	commands.Add(Command(command, value));
}

int RPGSkill::CommandsCount() const
{
	return commands.Num();
}

const RPGSkill::Command& RPGSkill::GetCommand(int index) const
{
	ensure(index >= 0 && index < commands.Num());
	return commands[index];
}
