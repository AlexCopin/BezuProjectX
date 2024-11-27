// Fill out your copyright notice in the Description page of Project Settings.


#include "GC_GameplayAbility_Character.h"

#include "GameplayTagsManager.h"
#include "GargoyleCraft/Include/GC_Macros.h"
#include <Abilities/Tasks/AbilityTask_PlayMontageAndWait.h>
#include <Abilities/Tasks/AbilityTask_WaitGameplayEvent.h>

UGC_GameplayAbility_Character::UGC_GameplayAbility_Character()
{
	ActivationBlockedTags.AddTag(MAKE_TAG("State.Moving.Forced"));
	ActivationBlockedTags.AddTag(MAKE_TAG("State.Stun"));
	ActivationBlockedTags.AddTag(MAKE_TAG("State.Dead"));
	TargetBlockedTags.AddTag(MAKE_TAG("State.Moving.Forced"));
	TargetBlockedTags.AddTag(MAKE_TAG("State.Stun"));
	TargetBlockedTags.AddTag(MAKE_TAG("State.Dead"));
}

void UGC_GameplayAbility_Character::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                    const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (ensure(AnimMontage)) 
	{
		PlayAnimTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,                   // Owning ability
			FName("Task_Melee"),    // Task instance name
			AnimMontage,            // The animation montage
			1.f,                   // Playback rate
			NAME_None,              // Starting section (default: none)
			false,                  // bStopWhenAbilityEnds
			1.0f                    // Root motion translation scale
		);
		//UAbilityTask_WaitGameplayEvent
		if (PlayAnimTask)
		{
			PlayAnimTask->OnBlendOut.AddDynamic(this, &UGC_GameplayAbility_Character::OnAnimCompleted);
			PlayAnimTask->OnCompleted.AddDynamic(this, &UGC_GameplayAbility_Character::OnAnimCompleted);
			PlayAnimTask->OnCancelled.AddDynamic(this, &UGC_GameplayAbility_Character::OnAnimCancelled);
			PlayAnimTask->OnInterrupted.AddDynamic(this, &UGC_GameplayAbility_Character::OnAnimCancelled);
			PlayAnimTask->ReadyForActivation();
		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT(" AnimMontage null in %s from %s"), *GetName(), *ActorInfo->AvatarActor->GetName());
		OnAnimCompleted();
	}
}

void UGC_GameplayAbility_Character::SetDuration()
{
	//empty override because animation is the trigger
}

void UGC_GameplayAbility_Character::DurationEnded()
{
	//empty override because animation is the trigger
}

void UGC_GameplayAbility_Character::OnAnimCompleted()
{
	UE_LOG(LogTemp, Log, TEXT("Animation completed!"));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGC_GameplayAbility_Character::OnAnimCancelled()
{
	UE_LOG(LogTemp, Log, TEXT("Animation Cancelled!"));
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}
