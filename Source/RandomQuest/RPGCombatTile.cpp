// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomQuest.h"
#include "RPGCombatTile.h"

RPGCombatTile::RPGCombatTile(Tile _tile) : tile(_tile)
{
	switch (tile)
	{
	case Center:
		x = 0.f;
		y = 0.f;
		break;
	case Up:
		x = 0.f;
		y = 1.f;
		break;
	case Down:
		x = 0.f;
		y = -1.f;
		break;
	case Left:
		x = -1.f;
		y = 0.f;
		break;
	case Right:
		x = 1.f;
		y = 0.f;
		break;
	case North:
		x = 0.f;
		y = 2.f;
		break;
	case NorthEast:
		x = 1.42f;
		y = 1.42f;
		break;
	case East:
		x = 2.f;
		y = 0.f;
		break;
	case SouthEast:
		x = 1.42f;
		y = -1.42f;
		break;
	case South:
		x = 0.f;
		y = -2.f;
		break;
	case SouthWest:
		x = -1.42f;
		y = -1.42f;
		break;
	case West:
		x = -2.f;
		y = 0.f;
		break;
	case NorthWest:
		x = -1.42f;
		y = 1.42f;
		break;
	case Count:
	case None:
	default:
		ensure(false);
		break;
	}
}

int RPGCombatTile::Distance(const RPGCombatTile& _tile)
{
	return static_cast<int>(FVector2D::Distance(FVector2D(x, y), FVector2D(_tile.x, _tile.y)));
}

int RPGCombatTile::Distance(Tile tileA, Tile tileB)
{
	return RPGCombatTile(tileA).Distance(RPGCombatTile(tileB));
}

void RPGCombatTile::UnitTests()
{
	ensure(Distance(Center, Center) == 0);
	ensure(Distance(Center, Up) == 1);
	ensure(Distance(Center, Down) == 1);
	ensure(Distance(Center, Left) == 1);
	ensure(Distance(Center, Right) == 1);
	ensure(Distance(Center, North) == 2);
	ensure(Distance(Center, East) == 2);
	ensure(Distance(Center, South) == 2);
	ensure(Distance(Center, West) == 2);
	ensure(Distance(Center, NorthEast) == 2);
	ensure(Distance(Center, NorthWest) == 2);
	ensure(Distance(Center, SouthEast) == 2);
	ensure(Distance(Center, SouthWest) == 2);

	ensure(Distance(Up, Center) == 1);
	ensure(Distance(Up, Up) == 0);
	ensure(Distance(Up, Down) == 2);
	ensure(Distance(Up, Left) == 1);
	ensure(Distance(Up, Right) == 1);
	ensure(Distance(Up, North) == 1);
	ensure(Distance(Up, East) == 2);
	ensure(Distance(Up, South) == 3);
	ensure(Distance(Up, West) == 2);
	ensure(Distance(Up, NorthEast) == 1);
	ensure(Distance(Up, NorthWest) == 1);
	ensure(Distance(Up, SouthEast) == 2);
	ensure(Distance(Up, SouthWest) == 2);

	ensure(Distance(Down, Center) == 1);
	ensure(Distance(Down, Up) == 2);
	ensure(Distance(Down, Down) == 0);
	ensure(Distance(Down, Left) == 1);
	ensure(Distance(Down, Right) == 1);
	ensure(Distance(Down, North) == 3);
	ensure(Distance(Down, East) == 2);
	ensure(Distance(Down, South) == 1);
	ensure(Distance(Down, West) == 2);
	ensure(Distance(Down, NorthEast) == 2);
	ensure(Distance(Down, NorthWest) == 2);
	ensure(Distance(Down, SouthEast) == 1);
	ensure(Distance(Down, SouthWest) == 1);

	ensure(Distance(Left, Center) == 1);
	ensure(Distance(Left, Up) == 1);
	ensure(Distance(Left, Down) == 1);
	ensure(Distance(Left, Left) == 0);
	ensure(Distance(Left, Right) == 2);
	ensure(Distance(Left, North) == 2);
	ensure(Distance(Left, East) == 3);
	ensure(Distance(Left, South) == 2);
	ensure(Distance(Left, West) == 1);
	ensure(Distance(Left, NorthEast) == 2);
	ensure(Distance(Left, NorthWest) == 1);
	ensure(Distance(Left, SouthEast) == 2);
	ensure(Distance(Left, SouthWest) == 1);

	ensure(Distance(Right, Center) == 1);
	ensure(Distance(Right, Up) == 1);
	ensure(Distance(Right, Down) == 1);
	ensure(Distance(Right, Left) == 2);
	ensure(Distance(Right, Right) == 0);
	ensure(Distance(Right, North) == 2);
	ensure(Distance(Right, East) == 1);
	ensure(Distance(Right, South) == 2);
	ensure(Distance(Right, West) == 3);
	ensure(Distance(Right, NorthEast) == 1);
	ensure(Distance(Right, NorthWest) == 2);
	ensure(Distance(Right, SouthEast) == 1);
	ensure(Distance(Right, SouthWest) == 2);

	ensure(Distance(North, Center) == 2);
	ensure(Distance(North, Up) == 1);
	ensure(Distance(North, Down) == 3);
	ensure(Distance(North, Left) == 2);
	ensure(Distance(North, Right) == 2);
	ensure(Distance(North, North) == 0);
	ensure(Distance(North, East) == 2);
	ensure(Distance(North, South) == 4);
	ensure(Distance(North, West) == 2);
	ensure(Distance(North, NorthEast) == 1);
	ensure(Distance(North, NorthWest) == 1);
	ensure(Distance(North, SouthEast) == 3);
	ensure(Distance(North, SouthWest) == 3);

	ensure(Distance(South, Center) == 2);
	ensure(Distance(South, Up) == 3);
	ensure(Distance(South, Down) == 1);
	ensure(Distance(South, Left) == 2);
	ensure(Distance(South, Right) == 2);
	ensure(Distance(South, North) == 4);
	ensure(Distance(South, East) == 2);
	ensure(Distance(South, South) == 0);
	ensure(Distance(South, West) == 2);
	ensure(Distance(South, NorthEast) == 3);
	ensure(Distance(South, NorthWest) == 3);
	ensure(Distance(South, SouthEast) == 1);
	ensure(Distance(South, SouthWest) == 1);

	ensure(Distance(East, Center) == 2);
	ensure(Distance(East, Up) == 2);
	ensure(Distance(East, Down) == 2);
	ensure(Distance(East, Left) == 3);
	ensure(Distance(East, Right) == 1);
	ensure(Distance(East, North) == 2);
	ensure(Distance(East, East) == 0);
	ensure(Distance(East, South) == 2);
	ensure(Distance(East, West) == 4);
	ensure(Distance(East, NorthEast) == 1);
	ensure(Distance(East, NorthWest) == 3);
	ensure(Distance(East, SouthEast) == 1);
	ensure(Distance(East, SouthWest) == 3);

	ensure(Distance(West, Center) == 2);
	ensure(Distance(West, Up) == 2);
	ensure(Distance(West, Down) == 2);
	ensure(Distance(West, Left) == 1);
	ensure(Distance(West, Right) == 3);
	ensure(Distance(West, North) == 2);
	ensure(Distance(West, East) == 4);
	ensure(Distance(West, South) == 2);
	ensure(Distance(West, West) == 0);
	ensure(Distance(West, NorthEast) == 3);
	ensure(Distance(West, NorthWest) == 1);
	ensure(Distance(West, SouthEast) == 3);
	ensure(Distance(West, SouthWest) == 1);

	ensure(Distance(NorthEast, Center) == 2);
	ensure(Distance(NorthEast, Up) == 1);
	ensure(Distance(NorthEast, Down) == 2);
	ensure(Distance(NorthEast, Left) == 2);
	ensure(Distance(NorthEast, Right) == 1);
	ensure(Distance(NorthEast, North) == 1);
	ensure(Distance(NorthEast, East) == 1);
	ensure(Distance(NorthEast, South) == 3);
	ensure(Distance(NorthEast, West) == 3);
	ensure(Distance(NorthEast, NorthEast) == 0);
	ensure(Distance(NorthEast, NorthWest) == 2);
	ensure(Distance(NorthEast, SouthEast) == 2);
	ensure(Distance(NorthEast, SouthWest) == 4);

	ensure(Distance(NorthWest, Center) == 2);
	ensure(Distance(NorthWest, Up) == 1);
	ensure(Distance(NorthWest, Down) == 2);
	ensure(Distance(NorthWest, Left) == 1);
	ensure(Distance(NorthWest, Right) == 2);
	ensure(Distance(NorthWest, North) == 1);
	ensure(Distance(NorthWest, East) == 3);
	ensure(Distance(NorthWest, South) == 3);
	ensure(Distance(NorthWest, West) == 1);
	ensure(Distance(NorthWest, NorthEast) == 2);
	ensure(Distance(NorthWest, NorthWest) == 0);
	ensure(Distance(NorthWest, SouthEast) == 4);
	ensure(Distance(NorthWest, SouthWest) == 2);

	ensure(Distance(SouthWest, Center) == 2);
	ensure(Distance(SouthWest, Up) == 2);
	ensure(Distance(SouthWest, Down) == 1);
	ensure(Distance(SouthWest, Left) == 1);
	ensure(Distance(SouthWest, Right) == 2);
	ensure(Distance(SouthWest, North) == 3);
	ensure(Distance(SouthWest, East) == 3);
	ensure(Distance(SouthWest, South) == 1);
	ensure(Distance(SouthWest, West) == 1);
	ensure(Distance(SouthWest, NorthEast) == 4);
	ensure(Distance(SouthWest, NorthWest) == 2);
	ensure(Distance(SouthWest, SouthEast) == 2);
	ensure(Distance(SouthWest, SouthWest) == 0);

	ensure(Distance(SouthEast, Center) == 2);
	ensure(Distance(SouthEast, Up) == 2);
	ensure(Distance(SouthEast, Down) == 1);
	ensure(Distance(SouthEast, Left) == 2);
	ensure(Distance(SouthEast, Right) == 1);
	ensure(Distance(SouthEast, North) == 3);
	ensure(Distance(SouthEast, East) == 1);
	ensure(Distance(SouthEast, South) == 1);
	ensure(Distance(SouthEast, West) == 3);
	ensure(Distance(SouthEast, NorthEast) == 2);
	ensure(Distance(SouthEast, NorthWest) == 4);
	ensure(Distance(SouthEast, SouthEast) == 0);
	ensure(Distance(SouthEast, SouthWest) == 2);
}
