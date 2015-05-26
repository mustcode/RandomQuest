// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGAttribute
{
public:
	RPGAttribute();
	~RPGAttribute();
	virtual void Randomize();

protected:

	FName name;
	int minValue;
	int maxValue;
	int value;
};
