// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include <EnhancedInputComponent.h>
#include "Projectile.h"


#include "PlayerCharacter.generated.h"

UCLASS()
class WORKSHOP2_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		int Health;

	UPROPERTY(EditAnywhere)
		float MovementSpeed;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile> Projectile;


public:
	// Sets default values for this character's properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* IA_Rotate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UInputAction* IA_Shoot;

	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
