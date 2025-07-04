// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ABCharacterItemInterface.generated.h"

class UABItemData;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UABCharacterItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARENABATTLEDEMO_API IABCharacterItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void TakeItem(UABItemData* InItemData) = 0;
};
