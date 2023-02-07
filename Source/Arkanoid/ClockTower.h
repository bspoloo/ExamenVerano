// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Publisher.h"
#include "ClockTower.generated.h"

/**
 * 
 */
UCLASS()
class ARKANOID_API AClockTower : public APublisher
{
	GENERATED_BODY()
private:   
	//The current time of this Clock Tower  
	FString State;

public:   
	//funcion que tomara el cambio de estado "cantidad de vidas" 
	void StateChanged();  

	//establece el tipo de estado actual enviado por el clock tower 
	void SetState(FString myState); 

	//retorna el estado que se establecio en SetState
	FORCEINLINE FString GetState() { return State; };
};
