// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGTrait.h"

RPGTrait::RPGTrait()
{
}

RPGTrait::RPGTrait(FName _name, int _value) : name(_name), value(_value)
{
}

RPGTrait::~RPGTrait()
{
}

FName RPGTrait::GetName() const
{
	return name;
}

int RPGTrait::GetValue() const
{
	return value;
}
