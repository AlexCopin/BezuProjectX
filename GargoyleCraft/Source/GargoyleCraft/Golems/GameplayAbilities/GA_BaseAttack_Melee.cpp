#include "GA_BaseAttack_Melee.h"

void UGA_BaseAttack_Melee::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
  Super::OnGiveAbility(ActorInfo, Spec);
  auto actorInfo = GetCurrentActorInfo();
  if(actorInfo)
    UE_LOG(LogTemp, Warning, TEXT("NameAvatarActor = %s"), *actorInfo->AvatarActor->GetName());
  auto spec = GetCurrentAbilitySpec();
  if(spec)
    UE_LOG(LogTemp, Warning, TEXT("HandleSpec = %s"), *spec->Handle.ToString());
}
