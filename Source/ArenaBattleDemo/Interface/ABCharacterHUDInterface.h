// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ABCharacterHUDInterface.generated.h"

class UABHUDWidget;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UABCharacterHUDInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARENABATTLEDEMO_API IABCharacterHUDInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 캐릭터에서 HUD 위젯을 설정할 때 사용
	virtual void SetupHUDWidget(UABHUDWidget* InHUDWidget) = 0;
};
