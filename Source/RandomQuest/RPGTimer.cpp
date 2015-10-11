// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGTimer.h"

RPGTimer::RPGTimer()
{
}

RPGTimer::RPGTimer(float _duration)
{
	Set(_duration);
}

RPGTimer::~RPGTimer()
{
}

void RPGTimer::Set(float seconds)
{
	duration = seconds;
	Reset();
}

void RPGTimer::Reset()
{
	time = duration;
	elapsedCount = 0;
}

int RPGTimer::Update(float deltaSeconds)
{
	ensure(time > 0.f);
	ensure(deltaSeconds >= 0.f);
	int elapsed = static_cast<int>(deltaSeconds / duration);
	deltaSeconds -= duration * elapsed;
	ensure(deltaSeconds >= 0.f && deltaSeconds <= duration);
	time -= deltaSeconds;
	if (time <= 0.f)
	{
		++elapsed;
		time += duration;
	}
	ensure(time > 0.f);
	elapsedCount += elapsed;
	return elapsed;
}

int RPGTimer::GetElapsedCount() const
{
	return elapsedCount;
}
