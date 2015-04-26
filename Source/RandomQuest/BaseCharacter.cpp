// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "BaseCharacter.h"
#include "CharacterObject.h"

void ABaseCharacter::Init(UCharacterObject* characterObject)
{
	character = characterObject;
}
