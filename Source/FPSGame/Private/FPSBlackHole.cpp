// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerShpereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerShpereComponent->SetSphereRadius(100);
	InnerShpereComponent->SetupAttachment(MeshComp);

	// 绑定事件
	InnerShpereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OverlapInnerShpere);

	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OuterShpereComp"));
	OuterSphereComponent->SetSphereRadius(3000); // 巨大的球体,比Level还要大
	OuterSphereComponent->SetupAttachment(MeshComp);
}

void AFPSBlackHole::OverlapInnerShpere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor) {
		OtherActor->Destroy();
	}
}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();

	AFPSBlackHole::TestLog();

}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 发现所有可 collide 和 simulate physics 的 overlapping components
	TArray<UPrimitiveComponent*> OverlappingComps;
	OuterSphereComponent->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++) {
		UPrimitiveComponent* PrimComp = OverlappingComps[i];
		if (PrimComp&&PrimComp->IsSimulatingPhysics()) {

			const float SphereRadius = OuterSphereComponent->GetScaledSphereRadius();
			const float ForceStrength = -2000;

			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

void AFPSBlackHole::TestLog()
{
	// 输出到屏幕
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("参数-1表示无需更新或刷新此消息,5f表示显示时间"));

	// 控制台中打印
	UE_LOG(LogTemp, Log, TEXT("Log显示灰色"));
	UE_LOG(LogTemp, Warning, TEXT("Warning显示黄色"));
	UE_LOG(LogTemp, Error, TEXT("Error显示红色"));

	// 输出变量 TEXT 防止中文乱码
	FString msg = TEXT("float用'%f'表示,int用'%i'表示,string用'%s'表示,需要加*  ");
	FVector vector = GetActorLocation();
	float f = 5.f;
	int a = 50;
	UE_LOG(LogTemp, Warning, TEXT("%s, float: %f, float: %f, int: %i"), *msg, vector.Z, f, a);
}

