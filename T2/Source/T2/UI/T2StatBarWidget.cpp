// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/T2StatBarWidget.h"
#include "Components/ProgressBar.h"

UT2StatBarWidget::UT2StatBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UT2StatBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetStatBarColor(StatBarColor);
}

void UT2StatBarWidget::SetStatBarRatio(float Ratio)
{
	if (StatBar)
	{
		StatBar->SetPercent(Ratio);
	}
}

void UT2StatBarWidget::SetStatBarColor(FLinearColor NewColor)
{
	if (StatBar)
	{
		StatBar->SetFillColorAndOpacity(NewColor);
	}
}
