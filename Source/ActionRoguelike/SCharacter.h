// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>
#include <Runtime/Engine/Classes/Camera/CameraComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractComponent.h" //引入ActorComponent，这个东西就是一个组件了，需要U
#include "SCharacter.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Attack")//类别让代码更清晰
	UAnimMontage* AttackAnim;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp = nullptr;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass = nullptr;

	UPROPERTY(VisibleAnywhere)
	USInteractComponent* InteractionComp = nullptr;

	void MoveForward(float value);
	void MoveRight(float value);
	void PrimaryAttack();
	void PrimaryInteraction();

	FTimerHandle TimeHandle_PrimaryAttack; //计时器相关
	void PrimaryAttack_TimeElapsed();//计时结束后事件

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
