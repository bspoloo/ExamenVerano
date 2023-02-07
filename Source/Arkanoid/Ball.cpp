// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Brick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TwoBall.h"
#include "ThreeBall.h"
#include "Publisher.h" 
#include "ClockTower.h"
#include "Paddle.h"


// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("StaticMesh'/Game/Assets/Meshes/SM_Ball.SM_Ball'"));
	SM_Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	SM_Ball->SetSimulatePhysics(true);
	SM_Ball->SetEnableGravity(false);
	SM_Ball->SetConstraintMode(EDOFMode::XZPlane);
	SM_Ball->SetStaticMesh(BallMesh.Object);
	SM_Ball->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Ball->SetCollisionProfileName(TEXT("PhsysiscActor"));
	SetRootComponent(SM_Ball);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 0.0f;
	ProjectileMovement->MaxSpeed = 0.0f;
	ProjectileMovement->bShouldBounce = true; //Debe rebotar
	ProjectileMovement->Bounciness = 1.1f; //Rebote
	ProjectileMovement->Friction = 0.0f; //Friccion


	Damage = 1.0f;
}

void ABall::Launch(bool validacion)
{
	if (validacion == true)
	{
		if (!BallLaunched)
		{
			SM_Ball->AddImpulse(FVector(160.0f, 0.0f, 200.0f), FName(), true);
			BallLaunched = true;
		}
	}
	else if (validacion == false)
	{
		if (!BallLaunched)
		{
			SM_Ball->AddImpulse(FVector(0,0,-100), FName(), true);
			BallLaunched = true;
		}
	}
	
}

UStaticMeshComponent* ABall::GetBall()
{
	return SM_Ball;
}

void ABall::DestroyBall()
{
	Destroy();
}


void ABall::Destroyed()
{
	//Log Error if its Clock Tower is NULL
	if (!ClockTower) 
	{
		UE_LOG(LogTemp, Error, TEXT("Destroyed():ClockTower es NULL, este seguro de inicializarlo"));
		return; 
	}
			
	//Unsubscribe from the Clock Tower if it's destroyed
	//desubscribe del clo tower si este llega a ser destruido 
	ClockTower->UnSubscribe(this);
}

void ABall::Update(APublisher* Publisher)
{
	//en esta funcion se llama a la funcion de morph el cual tiene almacenado las rutinas
	Morph();

}

void ABall::Morph()
{
	//validamos si el clock tower existe
	if (!ClockTower)
	{
		UE_LOG(LogTemp, Error, TEXT("Morph(): ClockTower es NULL, este seguro de inicializarlo."));
		return;
	}
	//obtiene el estado actual  
	FString Time = ClockTower->GetState();

	// se toma el estado y se hace la comparacion para ejecutar la rutina 
	if (!Time.Compare("Reducir vida"))
	{
		//ejecuta la funcion de reducir la cantidad de vida del paddle      
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("cantidad de vida reducida"), *Time));

		//casteamos el paddle y con un puntero vamos reduciendo su vida cada ves que la comparacion sea valida
		APaddle* Paddle = Cast<APaddle>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		//con el paddel casteado, hacemos un puntero y reducimos su vida
		Paddle->DecreaseOfLife(Damage);


	}
	
}

void ABall::SetClockTower(AClockTower* myClockTower)
{
	//validamos que el clock tower exista 
	if (!myClockTower)
	{
		UE_LOG(LogTemp, Error, TEXT("ClockTower es NULL, este seguro de inicializarlo."));
		return;
	}    
	//establecemos el clock tower ingresodo, para que sea el actual utilizado 
	ClockTower = myClockTower;
	//con un puntero llamamos a la funcion Subscribe y subscribimos a esta clase
	ClockTower->Subscribe(this);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


