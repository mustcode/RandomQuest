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
		FName param;
		float time;
		float value;
		Command(FName _command, FName _param, float _time, float _value) : command(_command), param(_param), time(_time), value(_value){}
	};

	RPGSkill(FText _displayName, FText _description, FName _name, FName _variationOf, bool _isUsableInCombat, bool _isUsableOutOfCombat, bool _canSelectTargetAlly, bool _canSelectTargetEnemy);
	~RPGSkill();

	FText GetDisplayName() const;
	FText GetDescription() const;
	FName GetName() const;
	FName GetVariationOf() const;
	bool IsUsableInCombat() const;
	bool IsUsableOutOfCombat() const;
	bool CanSelectTargetAlly() const;
	bool CanSelectTargetEnemy() const;

	void AddCommand(FName command, FName param, float time, float value);
	void AddCommand(Command command);
	int CommandsCount() const;
	const Command& GetCommand(int index) const;
	const TArray<Command>& GetCommands() const;

	void AddCost(FName resource, int value);
	int GetCost(FName resource) const;
	const TMap<FName, int>& GetCosts() const;

protected:
	FText displayName;
	FText description;
	FName name;
	FName variationOf;
	bool isUsableInCombat;
	bool isUsableOutOfCombat;
	bool canSelectTargetAlly;
	bool canSelectTargetEnemy;
	TArray<Command> commands;
	TMap<FName, int> costs;
};
