// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGSkill
{
public:
	
	struct Command
	{
		FName command;
		float value;
		Command(FName cmd, float val) : command(cmd), value(val){}
	};

	RPGSkill();
	~RPGSkill();

	void AddCommand(FName command, float value);
	int CommandsCount() const;
	const Command& GetCommand(int index) const;

protected:

	FName name;
	TArray<Command> commands;
};
