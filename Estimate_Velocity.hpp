void* Original_Estimate_Velocity_Caller;

void __thiscall Redirected_Estimate_Velocity(void* Entity, float* Velocity)
{
	static std::unordered_set<void*> Invalids =
	{
		(void*)((unsigned __int32)Client_Module + 6329708),

		(void*)((unsigned __int32)Client_Module + 6332260)
	};

	if (Invalids.contains(*(void**)Entity) == 1)
	{
		(decltype(&Redirected_Estimate_Velocity)(Original_Estimate_Velocity_Caller))(Entity, Velocity);
	}
	else
	{
		using Calculate_Velocity_Type = void(__thiscall*)(void* Entity);

		Calculate_Velocity_Type((unsigned __int32)Client_Module + 290704)(Entity);

		Velocity[0] = *(float*)((unsigned __int32)Entity + 136);

		Velocity[1] = *(float*)((unsigned __int32)Entity + 140);

		Velocity[2] = *(float*)((unsigned __int32)Entity + 144);
	}
}