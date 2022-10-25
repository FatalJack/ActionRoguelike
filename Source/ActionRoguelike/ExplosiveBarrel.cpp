// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>("Cube");
	RootComponent = Cube;
	Cube->SetSimulatePhysics(true);
	Cube->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);

	Force = CreateDefaultSubobject<URadialForceComponent>("Force");
	Force->SetupAttachment(Cube);
	Force->ForceStrength = 700.0f;
	Force->Radius = 750.0f;
	Force->bImpulseVelChange = true;
	
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)//完整参数形式，不完整则无法绑定响应事件
{
	Force->FireImpulse();
	UE_LOG(LogTemp, Log, TEXT("OnActorHit in Explosive Barrel"));

	// %s = string
	// %f = float
	// logs: "OtherActor: MyActor_1, at gametime: 124.4" 
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}

void AExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Cube->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnActorHit);//响应事件绑定，绑定的是UFUNCTION
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

