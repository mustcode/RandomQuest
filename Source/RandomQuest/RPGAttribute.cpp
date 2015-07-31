// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGAttribute.h"
#include "RPGDice.h"

RPGAttribute::RPGAttribute()
{
}

RPGAttribute::RPGAttribute(FName _name, int _minValue, int _maxValue)
	: name(_name)
	, minValue(_minValue)
	, maxValue(_maxValue)
	, value(_minValue)
{
}

RPGAttribute::~RPGAttribute()
{
}

FName RPGAttribute::GetName() const
{
	return name;
}

int RPGAttribute::GetValue() const
{
	return value;
}

void RPGAttribute::SetValue(int _value, bool clampValue)
{
	value = _value;
	if (clampValue)
		value = FMath::Clamp(value, minValue, maxValue);
}

void RPGAttribute::Increase(int _value, bool clampValue)
{
	value += _value;
	if (clampValue)
		value = FMath::Clamp(value, minValue, maxValue);
}

void RPGAttribute::Decrease(int _value, bool clampValue)
{
	value -= _value;
	if (clampValue)
		value = FMath::Clamp(value, minValue, maxValue);
}

int RPGAttribute::GetMaxValue() const
{
	return maxValue;
}

int RPGAttribute::GetMinValue() const
{
	return minValue;
}

void RPGAttribute::SetMaxValue(int _maxValue)
{
	maxValue = _maxValue;
}

void RPGAttribute::SetMinValue(int _minValue)
{
	minValue = _minValue;
}

void RPGAttribute::SetValueToMax()
{
	value = maxValue;
}

void RPGAttribute::SetValueToMin()
{
	value = minValue;
}
