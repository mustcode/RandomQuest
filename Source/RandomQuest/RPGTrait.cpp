// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGTrait.h"

RPGTrait::RPGTrait()
{
}

RPGTrait::RPGTrait(FName _name) : name(_name)
{
}

RPGTrait::~RPGTrait()
{
}

FName RPGTrait::GetName() const
{
	return name;
}

void RPGTrait::SetProperty(FName name, int value)
{
	if (properties.Contains(name))
		properties[name] = value;
	else
		properties.Add(name, value);
}

int RPGTrait::GetProperty(FName name) const
{
	ensure(properties.Contains(name));
	return properties[name];
}

bool RPGTrait::HasProperty(FName name) const
{
	return properties.Contains(name);
}
