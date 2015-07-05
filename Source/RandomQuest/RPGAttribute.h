// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGAttribute
{
public:
	RPGAttribute();
	RPGAttribute(FName _name, int _minValue, int _maxValue);
	~RPGAttribute();
	int GetValue() const;
	void SetValue(int _value, bool clampValue = true);
	void Increase(int _value, bool clampValue = true);
	void Decrease(int _value, bool clampValue = true);
	int GetMaxValue() const;
	int GetMinValue() const;
	void SetMaxValue(int _maxValue);
	void SetMinValue(int _minValue);
	void SetValueToMax();
	void SetValueToMin();

protected:

	FName name;
	int minValue;
	int maxValue;
	int value;
};
