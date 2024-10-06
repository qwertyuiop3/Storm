struct Global_Variables_Structure
{
	__int8 Additional_Bytes_1[12];

	float Current_Time;

	float Frame_Time;

	__int8 Additional_Bytes_2[8];

	float Interval_Per_Tick;
};

void* Original_Interpolate_Caller;

__int8 __thiscall Redirected_Interpolate(void* Entity, float Time)
{
	if (Entity == *(void**)((unsigned __int32)Client_Module + 7498712))
	{
		Time = (*(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7096744))->Current_Time;

		*(__int32*)((unsigned __int32)Entity + 5328) -= *(__int32*)((unsigned __int32)Entity + 16);

		return (decltype(&Redirected_Interpolate)(Original_Interpolate_Caller))(Entity, Time);
	}

	return 1;
}