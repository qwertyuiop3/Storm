void* Original_Draw_Effect_Caller;

__int8 __thiscall Redirected_Draw_Effect(void* Effect, void* Unknown_Parameter_1, void* Unknown_Parameter_2)
{
	using Get_Effect_Name_Type = char*(__thiscall*)(void* Effect);

	if (__builtin_strstr(Get_Effect_Name_Type((unsigned __int32)Client_Module + 1423120)((void*)((unsigned __int32)Effect - 8)), "ecloud_ca") == nullptr)
	{
		return (decltype(&Redirected_Draw_Effect)(Original_Draw_Effect_Caller))(Effect, Unknown_Parameter_1, Unknown_Parameter_2);
	}

	return 0;
}