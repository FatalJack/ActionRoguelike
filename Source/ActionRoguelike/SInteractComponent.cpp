// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractComponent.h"
#include <ActionRoguelike/SGamePlayInterface.h>

// Sets default values for this component's properties
USInteractComponent::USInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractComponent::PrimaryInteract()
{
	FHitResult Hit;
	FVector Start;
	FRotator StartRot;
	GetOwner()->GetActorEyesViewPoint(Start, StartRot);
	FVector End = Start + (StartRot.Vector() * 10.0f);
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams);

	AActor* HitActor =  Hit.GetActor();
	if (HitActor) {
		if (HitActor->Implements<USGamePlayInterface>()) {
			APawn* MyPawn = Cast<APawn>(GetOwner());//这个cast就是一个投射，安全的，把Actor变成Pawn
			ISGamePlayInterface::Execute_Interact(HitActor, MyPawn);//接口执行者execute，被交互的物体就是接受者implement
		}
	}
}

