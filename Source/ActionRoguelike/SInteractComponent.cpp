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
	
	//FHitResult Hit;
	FVector Start;
	FRotator StartRot;
	GetOwner()->GetActorEyesViewPoint(Start, StartRot);
	FVector End = Start + (StartRot.Vector() * 200);
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ObjectQueryParams); //方法1，单个物体但是不好用
		
	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	float r = 30.0f;
	Shape.SetSphere(r);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, Start, End, FQuat::Identity, ObjectQueryParams, Shape);//方法2，扫描多个物体

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red; //条件判断

	for (auto Hit : Hits) {
		AActor* HitActor = Hit.GetActor();
		if (HitActor) {	
			if (HitActor->Implements<USGamePlayInterface>()) {
				APawn* MyPawn = Cast<APawn>(GetOwner());//这个cast就是一个投射，安全的，把Actor变成Pawn
				ISGamePlayInterface::Execute_Interact(HitActor, MyPawn);//接口执行者execute，被交互的物体就是接受者implement
				break;//确保不会一键多交互
			}
		}
		
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, r, 32, LineColor, false, 2.0f);
		
	}	
	DrawDebugLine(GetWorld(), Start, End, LineColor, false, 2.0f, .0f, 10.0f);
	
}

