// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGDamageInfo.h"

RPGDamageInfo::RPGDamageInfo()
	: attackRating(0)
	, attackBonus(0)
	, attackRolled(0)
	, defenseRating(0)
	, defenseBonus(0)
	, defenseRolled(0)
	, damageRating(0)
	, damageBonus(0)
	, damageRolled(0)
	, isCritical(false)
	, isFumbled(false)
{
}
