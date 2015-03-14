// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGDice.h"

int RPGDice::Roll(DiceType diceType)
{
	return FMath::RandRange(1, static_cast<int>(diceType));
}

int RPGDice::Roll(int diceCount, DiceType diceType)
{
	int total = 0;
	for (int i = 0; i < diceCount; ++i)
		total += Roll(diceType);
	return total;
}

int RPGDice::Roll(int diceCount, DiceType diceType, int* results)
{
	int total = 0;
	for (int i = 0; i < diceCount; ++i)
	{
		int score = Roll(diceType);
		results[i] = score;
		total += score;
	}
	return total;
}

int RPGDice::Roll(int diceCount, DiceType diceType, TArray<int>& results)
{
	int total = 0;
	for (int i = 0; i < diceCount; ++i)
	{
		int score = Roll(diceType);
		results.Add(score);
		total += score;
	}
	return total;
}
