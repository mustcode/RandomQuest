// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "CharacterObject.h"
#include "RPGCharacter.h"


UCharacterObject::UCharacterObject() : character(nullptr)
{
}

UCharacterObject::~UCharacterObject()
{
	if (character)
		delete character;
}

void UCharacterObject::Init()
{
	character = new RPGCharacter;
	character->Randomize();
}
