// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGTrait.h"

RPGTrait::RPGTrait()
{
}

RPGTrait::RPGTrait(FText _displayName, FText _description, FName _name)
	: displayName(_displayName)
	, description(_description)
	, name(_name)
{
}

RPGTrait::~RPGTrait()
{
}

FText RPGTrait::GetDisplayName() const
{
	return displayName;
}

FText RPGTrait::GetDescription() const
{
	return description;
}

FName RPGTrait::GetName() const
{
	return name;
}

void RPGTrait::SetProperty(FName name, Property value)
{
	if (properties.Contains(name))
		properties[name] = value;
	else
		properties.Add(name, value);
}

RPGTrait::Property RPGTrait::GetProperty(FName name) const
{
	ensure(properties.Contains(name));
	return properties[name];
}

bool RPGTrait::HasProperty(FName name) const
{
	return properties.Contains(name);
}

const TMap<FName, RPGTrait::Property>& RPGTrait::GetProperties() const
{
	return properties;
}
