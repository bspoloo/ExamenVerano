// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBound.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Paddle_PlayerController.h"
#include "Paddle.h"
#include "Publisher.h"



// Sets default values
ABallBound::ABallBound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionBall = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collision ball"));
	BoxCollisionBall->SetBoxExtent(FVector(40, 40, 40));
	/*Damage = 1.0;*/
}

// Called when the game starts or when spawned
void ABallBound::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollisionBall->OnComponentBeginOverlap.AddDynamic(this, &ABallBound::OnOverlapBegin);
	PlayerControllerREF = Cast<APaddle_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

//=============================================================================================
	//Spawneamos al Clock Tower
	ClockTower = GetWorld()->SpawnActor<AClockTower>(AClockTower::StaticClass());

	//Spawneamos al subscritor(Ball) y establecemos nuestro clock tower
	Ball = GetWorld()->SpawnActor<ABall>(ABall::StaticClass());
	Ball->Launch(false);
	//con el puntero establecemos nuestro clock tower
	Ball->SetClockTower(ClockTower);


}

void ABallBound::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweet, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Ball")) {
		OtherActor->Destroy();

		//APaddle* Paddle = Cast<APaddle>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		//Paddle->DecreaseOfLife(Damage);

		PlayerControllerREF->SpawnNewBall();

		//=======================================================

		//si la Ball entra en la capsula de colicion entonces con un puntero llamamos a SetState establecemos el estado de este
		ClockTower->SetState("Reducir vida");
	}



	if (OtherActor->ActorHasTag("Two")) {
		OtherActor->Destroy();
	}

	if (OtherActor->ActorHasTag("Three")) {
		OtherActor->Destroy();
	}

}

// Called every frame
void ABallBound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


