// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGCharacter;
class RPGItemInstance;

/**
 * 
 */
struct RANDOMQUEST_API RPGCombatRating
{
	struct Score
	{
		Score() : value(0), modifier(0) {}
		int value;
		int modifier;
	};

	struct Damage
	{
		Score damage;
		FName type;
	};

	struct AttackRating
	{
		Score attack;
		Score critialChance;
		TArray<Damage> damages;
	};

	struct DefenseRating
	{
		Score defense;
		Score counterChance;
	};

	RPGCombatRating();

	AttackRating meleeAttack;
	AttackRating rangedAttack;
	
	DefenseRating meleeDefense;
	DefenseRating rangedDefense;

	TMap<FName, int> damageResistance;
	Score initiative;

	RPGCharacter* character;
	TArray<RPGItemInstance*> equipments;
};
