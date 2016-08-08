// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
struct RANDOMQUEST_API RPGDamageInfo
{
	RPGDamageInfo();

	int amount;
	bool isCritical;
	bool isFumbled;
	FName damageType;
};
