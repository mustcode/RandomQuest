// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
*
*/
class RANDOMQUEST_API RPGCombatTile
{
public:

	enum Tile
	{
		Center,
		Up,
		Down,
		Left,
		Right,
		North,
		NorthEast,
		East,
		SouthEast,
		South,
		SouthWest,
		West,
		NorthWest,
		Count,
		None
	};
	
	RPGCombatTile(Tile _tile);
	Tile tile;

	int Distance(const RPGCombatTile& _tile);
	static int Distance(Tile tileA, Tile tileB);

	static void UnitTests();

private:
	float x, y;
};
