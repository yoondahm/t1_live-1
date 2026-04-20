// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActor.h"
#include "T2Actor.h"

// Sets default values
AMainActor::AMainActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainActor::BeginPlay()
{
	Super::BeginPlay();
	
	FVector Location(0.0f, 0.0f, 260.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	
	T2Actor = GetWorld()->SpawnActor<AT2Actor>(Location, Rotation);
	
	T2Actor->SetLifeSpan(.5f);
}

// Called every frame
void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

