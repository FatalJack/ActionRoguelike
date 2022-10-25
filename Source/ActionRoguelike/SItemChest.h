// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGamePlayInterface.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "SItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISGamePlayInterface //引入接口，不要忘了include
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn); //在C++中重写NativeEvent修饰的函数
public:	
	// Sets default values for this actor's properties
	ASItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
