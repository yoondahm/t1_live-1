// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T2Actor.generated.h"

UCLASS()
class T2_API AT2Actor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AT2Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) // UPROPERTY: 언리얼 에디터 상에서 관리받는 변수
	class UStaticMeshComponent* Box;

private:
	UPROPERTY() // 이걸 붙이지 않으면 Reference count를 세지 않음. -> GC가 수거해 갈 위험
	class UT2Object* T2Object;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Hp = 100; // OS와 관련없이 일관된 행동 보장 (비트 수 명시)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Mp = 50;

	float Speed = 3.0f;
};
