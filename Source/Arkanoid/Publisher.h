// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subscriber.h"
#include "Publisher.generated.h"

UCLASS()
class ARKANOID_API APublisher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APublisher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:   //The Subscribers of this Publisher 
	



// esta clase es como nuestro publicador, notificara a todos los subscriptores de cualquier observacion hecha por el clock tower
	//creamos un TArray que almacenara los subscriptores
	UPROPERTY() 
	TArray<AActor*> Subscribers = TArray<AActor*>(); 
public:    
	//funcion virtual que subscribira a los subscriptores

	virtual void Subscribe(AActor* Subscriber);  

	//Remueve al subscriptor del TArray
	virtual void UnSubscribe(AActor* SubscriberToRemove);

	//Notificara a los subscriptores de que hubo un cambio
	virtual void NotifySubscribers(); 
};
