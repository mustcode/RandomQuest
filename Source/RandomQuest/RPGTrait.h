// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGTrait
{
public:
	RPGTrait();
	RPGTrait(FName _name, int _value);
	~RPGTrait();

	FName GetName() const;
	int GetValue() const;

protected:
	FName name;
	int value;
};
