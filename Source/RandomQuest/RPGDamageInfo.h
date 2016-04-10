// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
struct RANDOMQUEST_API RPGDamageInfo
{
	RPGDamageInfo();

	int attackRating;
	int attackBonus;
	int attackRolled;

	int defenseRating;
	int defenseBonus;
	int defenseRolled;

	int damageRating;
	int damageBonus;
	int damageRolled;

	bool isCritical;
	bool isFumbled;
	FName damageType;
};
