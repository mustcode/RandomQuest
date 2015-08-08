// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GameDataComponent.h"
#include "BaseCharacter.generated.h"

class UCharacterObject;

UCLASS(ClassGroup = RPG)
class RANDOMQUEST_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ABaseCharacter();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = RPG)
	void Init(UCharacterObject* characterObject);

	UFUNCTION(BlueprintCallable, Category = RPG)
	bool TryUseSkill(FName name);

	UFUNCTION(BlueprintNativeEvent, Category = RPG)
	void OnExecuteSkillCommand(const TArray<FSkillCommand>& commands);

	UPROPERTY(BlueprintReadOnly, Category = RPG)
	UCharacterObject* character;

protected:
	virtual void OnExecuteSkillCommand_Implementation(const TArray<FSkillCommand>& commands);

	float activeSkillTime;
	int32 activeCommandIndex;
};
