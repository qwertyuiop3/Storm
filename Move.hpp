__int32 Extra_Commands;

__int32 Chainsaw_Cycles;

void* Original_Move_Caller;

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 7498712);

	using Run_Prediction_Type = void(__cdecl*)();

	if (Local_Player != nullptr)
	{
		Redirected_Read_Packets(Final);

		Local_Player = *(void**)((unsigned __int32)Client_Module + 7498712);

		Run_Prediction_Type((unsigned __int32)Engine_Module + 527776)();

		Redirected_Update_Animations();

		using Fire_Events_Type = void(__cdecl*)();

		Fire_Events_Type((unsigned __int32)Engine_Module + 521648)();

		Update_Animation_Time = (*(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7096744))->Time;

		Update_Animation_Type = 1;

		Redirected_Update_Animations();

		Update_Animation_Type = 0;
	}

	Extra_Commands = -1;

	Move_Label:
	{
		(decltype(&Redirected_Move)(Original_Move_Caller))(Unknown_Parameter, Final);

		Run_Prediction_Type((unsigned __int32)Engine_Module + 527776)();

		if (Local_Player != nullptr)
		{
			Chainsaw_Cycles += 1 + (Chainsaw_Cycles == 0);

			static float Deploy_Time;

			Chainsaw_Cycles *= *(float*)((unsigned __int32)Local_Player + 3872) == Deploy_Time;

			Deploy_Time = *(float*)((unsigned __int32)Local_Player + 3872);
		}

		if (Extra_Commands > 0)
		{
			Extra_Commands -= 1;

			goto Move_Label;
		}
	}
}