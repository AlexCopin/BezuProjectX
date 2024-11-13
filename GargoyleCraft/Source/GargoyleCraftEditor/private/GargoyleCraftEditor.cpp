#include "GargoyleCraftEditor.h"

IMPLEMENT_GAME_MODULE(FGargoyleCraftEditorModule, GargoyleCraftEditor);

DEFINE_LOG_CATEGORY(GargoyleCraftEditor)

#define LOCTEXT_NAMESPACE "GargoyleCraftEditor"

void FGargoyleCraftEditorModule::StartupModule()
{
	UE_LOG(GargoyleCraftEditor, Warning, TEXT("GargoyleCraftEditor: Log Started"));
}

void FGargoyleCraftEditorModule::ShutdownModule()
{
	UE_LOG(GargoyleCraftEditor, Warning, TEXT("GargoyleCraftEditor: Log Ended"));
}

#undef LOCTEXT_NAMESPACE