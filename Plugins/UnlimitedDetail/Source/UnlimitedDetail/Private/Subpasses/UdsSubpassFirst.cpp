#include "UdsSubpassFirst.h"

void FUdsSubpassFirst::Upscale(FRDGBuilder& GraphBuilder, const FViewInfo& View, const FInputs& PassInputs)
{
	Data->FinalOutput = PassInputs.SceneColor; // later subpasses will override this, if enabled
}

void FUdsSubpassFirst::PostProcess(FRDGBuilder& GraphBuilder, const FViewInfo& View, const FInputs& PassInputs)
{
	// if we never ran the Upscale pass, make sure we get initialized before running the PostProcess pass
	if (!Data->FinalOutput.IsValid())
	{
		check(PassInputs.OverrideOutput.IsValid());
		Data->FinalOutput = PassInputs.OverrideOutput; // later subpasses will override this, if enabled
	}
}