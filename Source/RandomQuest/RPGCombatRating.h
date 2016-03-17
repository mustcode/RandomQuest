// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGCharacter;
class RPGItemInstance;

/**
 * 
 */
struct RANDOMQUEST_API RPGCombatRating
{
	RPGCombatRating();

	int attack;
	int attackBonus;
	int defense;
	int defenseBonus;
	int damage;
	int damageBonus;
	FName damageType;

	RPGCharacter* character;
	TArray<RPGItemInstance*> equipments;
};
