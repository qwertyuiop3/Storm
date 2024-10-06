void* Original_Move_Caller;

__int32 Extra_Commands;

void Redirected_Move(float Unknown_Parameter, __int8 Final)
{
	if (*(void**)((unsigned __int32)Client_Module + 7498712) != nullptr)
	{
		Redirected_Read_Packets(Final);

		using Fire_Events_Type = void(__cdecl*)();

		Fire_Events_Type((unsigned __int32)Engine_Module + 521648)();
	}

	Extra_Commands = -1;

	Move_Label:
	{
		(decltype(&Redirected_Move)(Original_Move_Caller))(Unknown_Parameter, Final);

		if (Extra_Commands > 0)
		{
			Extra_Commands -= 1;

			goto Move_Label;
		}
	}

	using Update_Animations_Type = void(__cdecl*)();

	Update_Animations_Type((unsigned __int32)Client_Module + 205296)();

	Update_Animation_Time = (*(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7096744))->Current_Time;

	Update_Animation_Type = 1;

	Update_Animations_Type((unsigned __int32)Client_Module + 205296)();

	Update_Animation_Type = 0;
}