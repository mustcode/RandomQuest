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

	void GenerateParty(int numOfMembers);
	RPGCharacter* GetCharacter(int index) const;
	const TArray<RPGCharacter*>& GetParty() const;

private:
	TArray<RPGCharacter*> party;
	int gold;
};
