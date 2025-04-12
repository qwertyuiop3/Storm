void* Original_Play_Footstep_Sound_Caller;

void __thiscall Redirected_Play_Footstep_Sound(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4, void* Unknown_Parameter_5, void* Unknown_Parameter_6)
{
	if (*(__int8*)((unsigned __int32)Client_Module + 8072736) <= *(__int8*)((unsigned __int32)Client_Module + 8072752))
	{
		(decltype(&Redirected_Play_Footstep_Sound)(Original_Play_Footstep_Sound_Caller))(Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4, Unknown_Parameter_5, Unknown_Parameter_6);
	}
}