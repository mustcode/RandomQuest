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
		float time;
		float value;
		Command(FName _command, float _time, float _value) : command(_command), time(_time), value(_value){}
	};

	RPGSkill(FName _name, FName _variationOf, bool _isNonCombatSkill);
	~RPGSkill();

	FName GetName() const;
	FName GetVariationOf() const;
	bool IsNonCombatSkill() const;

	void AddCommand(FName command, float time, float value);
	void AddCommand(Command command);
	int CommandsCount() const;
	const Command& GetCommand(int index) const;
	const TArray<Command>& GetCommands() const;

	void AddCost(FName resource, int value);
	int GetCost(FName resource) const;
	const TMap<FName, int>& GetCosts() const;

protected:
	FName name;
	FName variationOf;
	bool isNonCombatSkill;
	TArray<Command> commands;
	TMap<FName, int> costs;
};
