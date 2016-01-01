// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGTrait
{
public:
	RPGTrait();
	RPGTrait(FText _displayName, FText _description, FName _name);
	~RPGTrait();

	FText GetDisplayName() const;
	FText GetDescription() const;
	FName GetName() const;

	void SetProperty(FName name, int value);
	int GetProperty(FName name) const;
	bool HasProperty(FName name) const;
	const TMap<FName, int>& GetProperties() const;

protected:
	FText displayName;
	FText description;
	FName name;
	TMap<FName, int> properties;
};
