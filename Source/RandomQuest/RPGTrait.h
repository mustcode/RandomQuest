// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGTrait
{
public:

	struct Property
	{
		FName key;
		int value;

		Property() : value(0) {}
		Property(FName _key, int _value) : key(_key), value(_value) {}
	};

	RPGTrait();
	RPGTrait(FText _displayName, FText _description, FName _name);
	~RPGTrait();

	FText GetDisplayName() const;
	FText GetDescription() const;
	FName GetName() const;

	void SetProperty(FName name, Property value);
	Property GetProperty(FName name) const;
	bool HasProperty(FName name) const;
	const TMap<FName, Property>& GetProperties() const;

protected:
	FText displayName;
	FText description;
	FName name;
	TMap<FName, Property> properties;
};
