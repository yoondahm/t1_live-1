// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/T2PlayerHudWidget.h"
#include "UI/T2StatBarWidget.h"
#include "Components/T2AttributeComponent.h"

UT2PlayerHudWidget::UT2PlayerHudWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UT2PlayerHudWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	APawn* OwningPawn = GetOwningPlayerPawn();
	if (OwningPawn)
	{
		UT2AttributeComponent* AttributeComponent = OwningPawn->FindComponentByClass<UT2AttributeComponent>();
		
		if (AttributeComponent)
		{
			AttributeComponent->OnAttributeChanged.AddUObject(this, &UT2PlayerHudWidget::OnAttributeChanged);
			AttributeComponent->BroadcastAttributeChanged(ET2AttributeType::Stamina);
		}
	}
}

void UT2PlayerHudWidget::OnAttributeChanged(ET2AttributeType InAttributeType, float InValue)
{
	switch (InAttributeType)
	{
	case ET2AttributeType::Stamina:
		Stamina->SetStatBarRatio(InValue);
		break;
	case ET2AttributeType::Health:
		break;
	default:
		break;
	}
}
