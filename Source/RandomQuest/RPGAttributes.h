// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGDice.h"

/**
 * 
 */
class RANDOMQUEST_API RPGAttributes
{
public:

	enum Stat
	{
		STR,
		DEX,
		CON,
		INT,
		WIS,
		CHA,
		Count
	};

	RPGAttributes();
	~RPGAttributes();

protected:
	int stats[Stat::Count];
	int HP;
	int maxHP;
};