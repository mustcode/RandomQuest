// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGPrerequisite.h"

RPGPrerequisite::RPGPrerequisite()
{
}

RPGPrerequisite::RPGPrerequisite(FName _name) : name(_name)
{

}

RPGPrerequisite::~RPGPrerequisite()
{
}

FName RPGPrerequisite::GetName() const
{
	return name;
}
