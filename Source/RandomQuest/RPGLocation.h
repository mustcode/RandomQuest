// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class RPGDungeon;

/**
 * 
 */
class RANDOMQUEST_API RPGLocation
{
public:
	RPGLocation(const FName& locationName, const FName& locationType, RPGLocation* parentLocation);
	RPGLocation();
	virtual ~RPGLocation();
	
	void AddChild(RPGLocation* child);
	void SetParent(RPGLocation* newParent);
	void DetachFromParent();
	void DetachFromChildren();
	bool HasParent() const;
	bool HasChild(const FName& name) const;
	bool IsParentOf(RPGLocation* child) const;

	void AddGate(const FName& name);
	bool HasGate(const FName& name) const;
	void AddConnection(const FName& gateName, RPGLocation* connectTo, const FName& entrance);
	bool HasConnection(const FName& gateName, RPGLocation* connectTo, const FName& entrance) const;
	bool IsConnected(RPGLocation* connectTo) const;

	FName GetName() const { return name; }
	FName GetType() const { return type; }

	RPGLocation* GetChild(int32 index) const;
	int32 GetChildrenCount() const;

protected:

	struct Connection
	{
		RPGLocation* connectTo;
		FName entrance;
		Connection(RPGLocation* loc, const FName& ent) : connectTo(loc), entrance(ent){}
		FORCEINLINE bool operator == (const Connection& other) const { return connectTo == other.connectTo && entrance == other.entrance; }
	};

	struct Gate
	{
		FName name;
		TArray<Connection> connections;
		Gate(const FName& gateName) : name(gateName){}
		FORCEINLINE bool operator == (const Gate& other) const { return name == other.name; }
	};

	FName name;
	FName type;
	TArray<RPGLocation*> children;
	TArray<Gate> gates;
	RPGLocation* parent;
};
