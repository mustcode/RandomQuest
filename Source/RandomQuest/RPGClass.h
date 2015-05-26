// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RPGDice.h"

class RPGSkill;
class RPGTrait;

/**
 * 
 */
class RANDOMQUEST_API RPGClass
{
public:

	RPGClass();
	~RPGClass();

protected:

	FName name;
	FName statPreferences[3];
	TArray<RPGTrait*> traits;
	TArray<RPGSkill*> skills;
};
