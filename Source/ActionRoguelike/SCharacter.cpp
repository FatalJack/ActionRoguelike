// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");//创建默认目标，括号是名字。弹簧臂组件，可以用来绑定第三人称摄像头
	SpringArmComp->SetupAttachment(RootComponent);//建立一个连接
	SpringArmComp->bUsePawnControlRotation = true;//弹簧臂可以随着视角转动
	bUseControllerRotationYaw = false;//人物静止时不跟着视角一起旋转

	GetCharacterMovement()->bOrientRotationToMovement = true;//让人物移动时的方向随着视角方向旋转（模型）

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);//相机连在杆子上

	InteractionComp = CreateDefaultSubobject<USInteractComponent>("InteractionComp");
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteraction);
}

void ASCharacter::MoveForward(float value)
{
	//AddMovementInput(GetActorForwardVector(), value); //只是向前走
	FRotator ControllRot = GetControlRotation();
	ControllRot.Pitch = .0f;
	ControllRot.Roll = .0f;
	AddMovementInput(ControllRot.Vector(), value);//模型朝向可以跟随视角进行方向调整
}

void ASCharacter::MoveRight(float value)
{
	//AddMovementInput(GetActorRightVector(), value);//向量方向一直变，所以会一直转
	//正确的应该是按照视角方向走
	FRotator ControllRot = GetControlRotation();
	ControllRot.Pitch = .0f;
	ControllRot.Roll = .0f;
	FVector RightVector = FRotationMatrix(ControllRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimeHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);//延时
}

void ASCharacter::PrimaryInteraction()
{
	if (InteractionComp) {
		InteractionComp->PrimaryInteract();
	}
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector SwordLocation = GetMesh()->GetSocketLocation("Sword_Base");//获取骨骼网格体中相应的点的坐标

	FTransform SpawnTM = FTransform(GetControlRotation(), SwordLocation);//让射出的位置处于所想的地方，这里是剑尖
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;//释放者
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}


