// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Health = 20;
	UE_LOG(LogTemp, Warning, TEXT("Health is at: %d"), Health);
	Super::BeginPlay();
	
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y * MovementSpeed);
	AddMovementInput(RightDirection, MovementVector.X * MovementSpeed);

}

void APlayerCharacter::Jump(const FInputActionValue& Value)
{
	Super::Jump();
}

void APlayerCharacter::Rotate(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(-LookAxisVector.Y);
}

void APlayerCharacter::Shoot(const FInputActionValue& Value)
{
	FVector Location = GetActorLocation();
	FRotator Rotation = GetControlRotation();
	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Location, Rotation);
	MoveIgnoreActorAdd(SpawnedProjectile);
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//	SetActorLocation(GetActorLocation() + GetActorForwardVector());

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = CastChecked<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(IA_Rotate, ETriggerEvent::Triggered, this, &APlayerCharacter::Rotate);
		EnhancedInputComponent->BindAction(IA_Shoot, ETriggerEvent::Triggered, this, &APlayerCharacter::Shoot);


	}

}

