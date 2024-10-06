struct Command_Structure
{
	__int8 Additional_Bytes_1[4];

	__int32 Command_Number;

	__int32 Tick_Number;

	float Angles[3];

	float Move[3];

	__int32 Buttons;

	__int8 Additional_Bytes_2[9];

	__int32 Random_Seed;
};

struct Extended_Command_Structure
{
	__int32 Extra_Commands;
};

Extended_Command_Structure Extended_Commands[150];

void* Original_Run_Command_Caller;

void __thiscall Redirected_Run_Command(void* Prediction, void* Player, Command_Structure* Command, void* Unknown_Parameter)
{
	Extended_Command_Structure* Extended_Command = &Extended_Commands[Command->Command_Number % 150];

	*(__int32*)((unsigned __int32)Player + 5324) -= Extended_Command->Extra_Commands;

	(decltype(&Redirected_Run_Command)(Original_Run_Command_Caller))(Prediction, Player, Command, Unknown_Parameter);
}