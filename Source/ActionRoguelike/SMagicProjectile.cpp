// Fill out your copyright notice in the Description page of Project Settings.

#include "Particles/ParticleSystem.h"
#include "SMagicProjectile.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);//设置对所有通道的碰撞
	//SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);//只与Pawn重叠
	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);//设置类型
	//手动设置碰撞
														 
	SphereComp->SetCollisionProfileName("Projectile");//需要设置一个新的通道，这样其他的Projectile也可以用
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

