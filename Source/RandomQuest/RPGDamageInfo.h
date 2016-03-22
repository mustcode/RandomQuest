// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
struct RANDOMQUEST_API RPGDamageInfo
{
	RPGDamageInfo();

	int attack;
	int defense;
	int damage;
	bool isCritical;
	bool isFumbled;
	FName damageType;
};
