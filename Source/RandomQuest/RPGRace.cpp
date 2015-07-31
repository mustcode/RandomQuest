// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGRace.h"
#include "RPGTrait.h"

RPGRace::RPGRace(FName _name) : name(_name)
{
}

RPGRace::~RPGRace()
{
}

FName RPGRace::GetName() const
{
	return name;
}

void RPGRace::AddTrait(RPGTrait* trait)
{
	ensure(trait != nullptr);
	ensure(!traits.Contains(trait));
	traits.Add(trait);
}

int RPGRace::TraitsCount() const
{
	return traits.Num();
}

RPGTrait* RPGRace::GetTrait(int index) const
{
	ensure(index >= 0 && index < traits.Num());
	return traits[index];
}
