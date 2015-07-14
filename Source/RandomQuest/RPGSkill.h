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

	void SetName(FName toSet);
	void SetVariationOf(FName toSet);
	FName GetName() const;
	FName GetVariationOf() const;

	void AddCommand(FName command, float value);
	int CommandsCount() const;
	const Command& GetCommand(int index) const;

	void AddCost(FName resource, int value);
	int GetCost(FName resource) const;

protected:

	FName name;
	FName variationOf;
	TArray<Command> commands;
	TMap<FName, int> costs;
};
