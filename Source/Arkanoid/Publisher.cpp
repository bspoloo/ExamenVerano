// Fill out your copyright notice in the Description page of Project Settings.


#include "Publisher.h"

// Sets default values
APublisher::APublisher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APublisher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APublisher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APublisher::Subscribe(AActor* Subscriber)
{

	//Añade a un subscriptor al TArray

	Subscribers.Add(Subscriber); 
}

void APublisher::UnSubscribe(AActor* SubscriberToRemove)
{
	////Remueve a un subscriptor al TArray 
	Subscribers.Remove(SubscriberToRemove);
}

void APublisher::NotifySubscribers()
{
	//usamos un iterador para poder interactuar con los subscriptores almacenados 
	for (AActor* Actor : Subscribers)   {       
		//casteamos cada subscriptor almacenado  

		ISubscriber* Sub = Cast<ISubscriber>(Actor);       
		if (Sub)       
		{           
			//despues de ser casteado se llama a la funcion update de ISubscriber           
			Sub->Update(this);      
		}  
	} 
}

