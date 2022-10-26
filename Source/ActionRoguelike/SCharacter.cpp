// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");//����Ĭ��Ŀ�꣬���������֡����ɱ���������������󶨵����˳�����ͷ
	SpringArmComp->SetupAttachment(RootComponent);//����һ������
	SpringArmComp->bUsePawnControlRotation = true;//���ɱۿ��������ӽ�ת��
	bUseControllerRotationYaw = false;//���ﾲֹʱ�������ӽ�һ����ת

	GetCharacterMovement()->bOrientRotationToMovement = true;//�������ƶ�ʱ�ķ��������ӽǷ�����ת��ģ�ͣ�

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);//������ڸ�����

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
	//AddMovementInput(GetActorForwardVector(), value); //ֻ����ǰ��
	FRotator ControllRot = GetControlRotation();
	ControllRot.Pitch = .0f;
	ControllRot.Roll = .0f;
	AddMovementInput(ControllRot.Vector(), value);//ģ�ͳ�����Ը����ӽǽ��з������
}

void ASCharacter::MoveRight(float value)
{
	//AddMovementInput(GetActorRightVector(), value);//��������һֱ�䣬���Ի�һֱת
	//��ȷ��Ӧ���ǰ����ӽǷ�����
	FRotator ControllRot = GetControlRotation();
	ControllRot.Pitch = .0f;
	ControllRot.Roll = .0f;
	FVector RightVector = FRotationMatrix(ControllRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimeHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);//��ʱ
}

void ASCharacter::PrimaryInteraction()
{
	if (InteractionComp) {
		InteractionComp->PrimaryInteract();
	}
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector SwordLocation = GetMesh()->GetSocketLocation("Sword_Base");//��ȡ��������������Ӧ�ĵ������

	FTransform SpawnTM = FTransform(GetControlRotation(), SwordLocation);//�������λ�ô�������ĵط��������ǽ���
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;//�ͷ���
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}


