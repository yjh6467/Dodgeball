#include "LookAtActorComponent.h"
#include "DodgeballFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"

ULookAtActorComponent::ULookAtActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void ULookAtActorComponent::BeginPlay()
{
	Super::BeginPlay();

}
void ULookAtActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bCanSeeTarget = LookAtActor();
}

bool ULookAtActorComponent::LookAtActor()
{
	if (TargetActor == nullptr) return false;

	TArray<const AActor*> IgnoreActors = { GetOwner(), TargetActor };
	if (UDodgeballFunctionLibrary::CanSeeActor(GetWorld(),
		GetComponentLocation(),
		TargetActor,
		IgnoreActors))
	{
		FVector Start = GetOwner()->GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		GetOwner()->SetActorRotation(LookAtRotation);
		return true;
	}

	return false;
}
