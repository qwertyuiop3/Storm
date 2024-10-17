void* Original_Spawn_Grenade_Caller;

void __thiscall Redirected_Spawn_Grenade(void* Entity)
{
	using Set_Size_Type = void(__thiscall*)(void* Entity, float* Minimum, float* Maximum);

	float Minimum[3] =
	{
		-16.f,
		
		-16.f,
		
		-16.f
	};

	float Maximum[3] =
	{ 
		16.f,

		16.f,

		16.f
	};

	Set_Size_Type((unsigned __int32)Client_Module + 281664)(Entity, Minimum, Maximum);

	(decltype(&Redirected_Spawn_Grenade)(Original_Spawn_Grenade_Caller))(Entity);
}