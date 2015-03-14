// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

enum DiceType
{
	D4 = 4,
	D6 = 6,
	D8 = 8,
	D10 = 10,
	D12 = 12,
	D20 = 20,
	D100 = 100
};

/**
 * 
 */
class RANDOMQUEST_API RPGDice
{
public:
	static int Roll(DiceType diceType);
	static int Roll(int diceCount, DiceType diceType);
	static int Roll(int diceCount, DiceType diceType, int* results);
	static int Roll(int diceCount, DiceType diceType, TArray<int>& results);
};
