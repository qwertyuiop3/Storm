void* Original_Process_Movement_Caller;

void __thiscall Redirected_Process_Movement(void* Unknown_Parameter, void* Player, void* Move_Data)
{
	__int32 Stunned = *(__int32*)((unsigned __int32)Player + 20);

	if (Stunned == 2)
	{
		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7096744);
		
		Global_Variables->Current_Time *= -1;

		*(__int32*)((unsigned __int32)Move_Data + 36) &= ~1564;

		if (*(__int8*)((unsigned __int32)Player + 4636) == 1)
		{
			*(__int32*)((unsigned __int32)Move_Data + 36) |= 4u;
		}

		*(float*)((unsigned __int32)Move_Data + 44) = 0;

		*(float*)((unsigned __int32)Move_Data + 48) = 0;

		(decltype(&Redirected_Process_Movement)(Original_Process_Movement_Caller))(Unknown_Parameter, Player, Move_Data);

		Global_Variables->Current_Time *= -1;
	}
	else
	{
		(decltype(&Redirected_Process_Movement)(Original_Process_Movement_Caller))(Unknown_Parameter, Player, Move_Data);
	}
}