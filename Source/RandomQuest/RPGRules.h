// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGCharacter;

/**
 * 
 */
class RANDOMQUEST_API RPGRules
{
public:
	RPGRules();
	~RPGRules();

	void InitCharacter(RPGCharacter* character);

private:
	void RandomizeAttributes(RPGCharacter* character);

	int gold;
};
