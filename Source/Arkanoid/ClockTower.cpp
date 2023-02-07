// Fill out your copyright notice in the Description page of Project Settings.


#include "ClockTower.h"

void AClockTower::StateChanged()
{
	//llama a la funcion de NotifySubscribers, osea que notificara a todos los subscriptores del cambio observado
	NotifySubscribers();
}


void AClockTower::SetState(FString myState)
{
	// con el parametro insertado de tipo String, se iguala al parametro State
	State = myState;
	
	// luego se llama a la funcion de StateChanged 
	StateChanged();
}
