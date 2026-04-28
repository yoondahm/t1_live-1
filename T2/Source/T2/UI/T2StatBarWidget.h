// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "T2StatBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class T2_API UT2StatBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UT2StatBarWidget(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativePreConstruct() override;

public :
	void SetStatBarRatio(float Ratio);
	void SetStatBarColor(FLinearColor NewColor);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UProgressBar> StatBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StatBar)
	FLinearColor StatBarColor = FLinearColor::Red;
};
