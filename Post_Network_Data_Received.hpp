struct Prediction_Field_Structure
{
	__int32 Type;

	char* Name;

	__int32 Offset;

	unsigned __int16 Size;

	__int8 Additionals_Bytes_1[18];

	__int32 Bytes;

	__int8 Additionals_Bytes_2[12];

	__int32 Flat_Offset[2];
};

struct Prediction_Copy_Structure
{
	__int8 Additionals_Bytes_1[8];

	void* Destination;

	void* Source;

	__int8 Additional_Bytes_2[48];

	void Construct(void* Destination, void* Source, void* Handler)
	{
		using Construct_Type = void(__fastcall*)(void* Prediction_Copy, void* Unknown_Parameter, __int32 Type, void* Destination, __int8 Destination_Packed, void* Source, __int8 Source_Packed, __int32 Operation_Type, void* Handler);

		Construct_Type((unsigned __int32)Client_Module + 1564512)(this, nullptr, 2, Destination, 1, Source, 0, 3, Handler);
	}
};

Prediction_Copy_Structure Predicton_Copy;

void Predicton_Copy_Compare(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4, void* Unknown_Parameter_5, void* Unknown_Parameter_6, __int8 Within_Tolerance, void* Unknown_Parameter_7)
{
	Prediction_Field_Structure* Field = *(Prediction_Field_Structure**)((unsigned __int32)__builtin_frame_address(0) + 60);

	if (Field->Flat_Offset[0] == 5324)
	{
		if (*(__int32*)((unsigned __int32)Predicton_Copy.Destination + 20) != 0)
		{
			goto Copy_Label;
		}
	}

	if (Within_Tolerance == 1)
	{
		Copy_Label:
		{
			Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int32)Predicton_Copy.Destination + Field->Flat_Offset[0]), Field->Bytes, (void*)((unsigned __int32)Predicton_Copy.Source + Field->Flat_Offset[1]));
		}
	}
}

struct Prediction_Descriptor_Structure
{
	Prediction_Field_Structure* Fields;

	__int32 Size;

	__int8 Additional_Bytes_1[4];

	Prediction_Descriptor_Structure* Parent;

	__int8 Additional_Bytes_2[6];
};

void* Original_Post_Network_Data_Received_Caller;

void __thiscall Redirected_Post_Network_Data_Received(void* Unknown_Parameter, __int32 Commands_Acknowledged)
{
	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 7498712);

	void* Result = *(void**)((unsigned __int32)Local_Player + 900 + (150 - ((Commands_Acknowledged - 1) % 150 + 1) * 150 % -~150) * 4);

	if (Result != nullptr)
	{
		Predicton_Copy.Construct(Local_Player, Result, (void*)Predicton_Copy_Compare);

		using Transfer_Data_Type = __int32(__thiscall*)(Prediction_Copy_Structure* Prediction_Copy, void* Unknown_Parameter, __int32 Entity_Number, Prediction_Descriptor_Structure* Descriptor);

		Transfer_Data_Type((unsigned __int32)Client_Module + 1573744)(&Predicton_Copy, nullptr, -1, (Prediction_Descriptor_Structure*)((unsigned __int32)Client_Module + 7236480));
	}

	(decltype(&Redirected_Post_Network_Data_Received)(Original_Post_Network_Data_Received_Caller))(Unknown_Parameter, Commands_Acknowledged);
}