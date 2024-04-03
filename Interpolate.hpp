void* Original_Interpolate_Caller;

__int8 __thiscall Redirected_Interpolate(void* Entity, void* Unknown_Parameter)
{
	if (Entity == *(void**)((unsigned __int32)Client_Module + 7490392))
	{
		return (decltype(&Redirected_Interpolate)(Original_Interpolate_Caller))(Entity, Unknown_Parameter);
	}

	return 1;
}