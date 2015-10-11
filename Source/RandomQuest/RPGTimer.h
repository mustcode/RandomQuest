// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class RANDOMQUEST_API RPGTimer
{
public:
	RPGTimer();
	RPGTimer(float _duration);
	~RPGTimer();

	void Set(float seconds);
	void Reset();
	int Update(float deltaSeconds);
	int GetElapsedCount() const;

private:
	float time;
	float duration;
	int elapsedCount;
};
