#include "GA_BaseAttack_Melee.h"

#include "GargoyleCraft/BlueprintFunctionLibraries/AbilityTools.h"
#include "GargoyleCraft/GameplayAbilitySystem/Data/PDA_GameplayAbility.h"
#include "GargoyleCraft/GameplayAbilitySystem/GameplayEffects/GE_Damage.h"
#include "GargoyleCraft/Golems/Golem.h"
#include "GargoyleCraft/Include/GC_Macros.h"

void UGA_BaseAttack_Melee::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
  Super::OnGiveAbility(ActorInfo, Spec);
}

void UGA_BaseAttack_Melee::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto target = Cast<AGolem>(ActorInfo->AvatarActor)->GetTarget();
	if(!target)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	//---FX
	FGameplayCueParameters params;
	params.AbilityLevel = GetAbilityLevel();
	params.Instigator = ActorInfo->AvatarActor;
	params.Location = target->GetActorLocation();
	K2_AddGameplayCueWithParams(MAKE_TAG("GameplayCue.BasicMelee"), params);
	//---

	//---ApplyDamage
	if(auto IASC = Cast<IAbilitySystemInterface>(target))
	{
		UAbilityTools::ApplyDamage(ActorInfo->AbilitySystemComponent.Get(), IASC->GetAbilitySystemComponent(), AbilityData->AbilityData.Damage);
	}
	//---

	UE_LOG(LogTemp, Warning, TEXT("UGA_BaseAttack_Melee::ActivateAbility"));
}
