// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClockTower.h"
#include "BallBound.h"
#include "Subscriber.h"
#include "Morph.h"
#include "Ball.generated.h"

class UProjectileMovementComponent;
class AClockTower;
UCLASS()
// necesitamos hacer a esta clase un subscriptor, pero para eso necesitamos las funciones virtuales puras de ISubscriber y IMorph
// para hacer a una clase hija de una interfaz se añade "public ISubscriber, public IMorph"
class ARKANOID_API ABall : public AActor, public ISubscriber, public IMorph
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	virtual void Launch(bool validacion);

	bool BallLaunched;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Ball; //Malla

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UProjectileMovementComponent* ProjectileMovement; //Movimiento del proyectil

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCapsuleComponent* Collision;	//Campo de colision

	float SpeedModifierOnBounce = 1.02f; //Modificador de velocidad

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		UStaticMeshComponent* GetBall(); //Obtenemos la malla

	void DestroyBall(); //Destruccion de la pelota

//===========================================(implementacion)




private:
	//The Clock Tower of this Subscriber 

	// Para hacer funcionar el observcer se necesita un Clock tower que tomara el cambio de estado, en este caso seria el Clock tower
	UPROPERTY()
		AClockTower* ClockTower;

	//funcion que Desubscribe a este subscriptor
	virtual void Destroyed() override; public:

	//Llamada cuando el Plublisher cambia de estado, lo cual ejeecutara la rutina de este Subscriber 
	virtual void Update(class APublisher* Publisher) override;

	//Ejecuta la rutina de de este subscriptor
	virtual void Morph();

	//establece el Clocktower de este subscriptor 
	void SetClockTower(AClockTower* myClockTower);



	int Damage;
	
};
