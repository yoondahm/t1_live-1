// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T2Define.h"
#include "Blueprint/UserWidget.h"
#include "T2PlayerHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class T2_API UT2PlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UT2PlayerHudWidget(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeConstruct() override;

public:
	void OnAttributeChanged(ET2AttributeType InAttributeType, float InValue);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UT2StatBarWidget> Stamina;
};
