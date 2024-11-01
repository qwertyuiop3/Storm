void* Original_Process_Movement_Caller;

void __thiscall Redirected_Process_Movement(void* Unknown_Parameter, void* Player, void* Move_Data)
{
	if (*(__int32*)((unsigned __int32)Player + 5324) < 0)
	{
		*(__int32*)((unsigned __int32)Move_Data + 36) &= ~1564;

		*(__int32*)((unsigned __int32)Move_Data + 36) |= 4 * *(__int8*)((unsigned __int32)Player + 4636);

		*(double*)((unsigned __int32)Move_Data + 44) = 0.;
	}

	(decltype(&Redirected_Process_Movement)(Original_Process_Movement_Caller))(Unknown_Parameter, Player, Move_Data);

	void* Ability = *(void**)((unsigned __int32)Client_Module + 7644532 + (((*(unsigned __int32*)((unsigned __int32)Player + 7892) & 4095) - 4097) << 4));

	if (Ability != nullptr)
	{
		*(float*)((unsigned __int32)Ability + 1636) = 0.f;
	}
}