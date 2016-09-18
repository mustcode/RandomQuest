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

void RPGTrait::SetProperty(FName propertyName, Property value)
{
	if (properties.Contains(propertyName))
		properties[propertyName] = value;
	else
		properties.Add(propertyName, value);
}

RPGTrait::Property RPGTrait::GetProperty(FName propertyName) const
{
	ensure(properties.Contains(propertyName));
	return properties[propertyName];
}

bool RPGTrait::HasProperty(FName propertyName) const
{
	return properties.Contains(propertyName);
}

const TMap<FName, RPGTrait::Property>& RPGTrait::GetProperties() const
{
	return properties;
}
