struct Command_Structure
{
	__int8 Additional_Bytes_1[4];

	__int32 Command_Number;

	__int32 Tick_Number;

	float Angles[3];

	float Move[2];

	__int32 Frame_Number;

	__int32 Buttons;

	__int8 Additional_Bytes_2[9];

	__int32 Random_Seed;
};

struct Extended_Command_Structure
{
	__int32 Extra_Commands;

	__int32 Sequence_Shift;
};

Extended_Command_Structure Extended_Commands[150];

void* Original_Run_Command_Caller;

void __thiscall Redirected_Run_Command(void* Prediction, void* Player, Command_Structure* Command, void* Unknown_Parameter)
{
	Extended_Command_Structure* Extended_Command = &Extended_Commands[Command->Frame_Number];

	*(__int32*)((unsigned __int32)Player + 5324) -= Extended_Command->Extra_Commands + Extended_Command->Sequence_Shift;

	(decltype(&Redirected_Run_Command)(Original_Run_Command_Caller))(Prediction, Player, Command, Unknown_Parameter);

	if (__builtin_return_address(0) == (void*)((unsigned __int32)Client_Module + 423107))
	{
		*(__int32*)((unsigned __int32)Player + 5324) += Extended_Command->Sequence_Shift;

		Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7096744);

		Global_Variables->Current_Time = (*(__int32*)((unsigned __int32)Player + 5324) - 1) * Global_Variables->Interval_Per_Tick;
	}
}