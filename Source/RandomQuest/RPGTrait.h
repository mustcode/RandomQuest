// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGTrait
{
public:
	RPGTrait();
	RPGTrait(FName _name);
	~RPGTrait();

	FName GetName() const;

	void SetProperty(FName name, int value);
	int GetProperty(FName name) const;
	bool HasProperty(FName name) const;

protected:
	FName name;
	TMap<FName, int> properties;
};
