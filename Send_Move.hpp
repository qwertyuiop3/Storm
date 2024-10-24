void Redirected_Send_Move()
{
	struct Message_Structure
	{
		__int8 Message[160];

		void Construct(__int8* Data, unsigned __int32 Size)
		{
			Byte_Manager::Set_Bytes(0, Message, sizeof(Message), 0);

			*(void**)Message = (void*)((unsigned __int32)Engine_Module + 3501348);

			*(void**)((unsigned __int32)Message + 132) = Data;

			*(__int32*)((unsigned __int32)Message + 136) = Size;

			*(__int32*)((unsigned __int32)Message + 140) = Size * 8;
		}
	};

	Message_Structure Message;

	__int8 Data[4000];

	Message.Construct(Data, sizeof(Data));

	void* Client = *(void**)((unsigned __int32)Engine_Module + 4352236);

	__int32 Choked_Commands = *(__int32*)((unsigned __int32)Client + 19024);

	__int32 Commands_Queue = min(Choked_Commands + 1, 15);

	*(__int32*)((unsigned __int32)&Message + 88) = Commands_Queue;

	__int32 Extra_Commands_Queue = Choked_Commands + 1 - Commands_Queue;

	__int32 Backup_Commands = min(Extra_Commands_Queue, 7);

	*(__int32*)((unsigned __int32)&Message + 84) = Backup_Commands;

	__int32 From_Command_Number = -1;

	__int32 Next_Command_Number = *(__int32*)((unsigned __int32)Client + 19020) + Choked_Commands + 2;

	__int32 To_Command_Number = Next_Command_Number - Commands_Queue - Backup_Commands;

	Write_Command_Label:
	{
		using Write_Command_Type = __int8(__thiscall*)(void* Client, void* Unknown_Parameter_1, void* Data, __int32 From, __int32 To, void* Unknown_Parameter_2);

		Write_Command_Type((unsigned __int32)Client_Module + 691088)(*(void**)((unsigned __int32)Engine_Module + 5171072), nullptr, (void*)((unsigned __int32)&Message + 132), From_Command_Number, To_Command_Number, nullptr);

		From_Command_Number = To_Command_Number;

		To_Command_Number += 1;

		if (To_Command_Number != Next_Command_Number)
		{
			goto Write_Command_Label;
		}
	}

	void* Network_Channel = *(void**)(*(unsigned __int32*)((unsigned __int32)Engine_Module + 4352236) + 24);

	*(__int32*)((unsigned __int32)Network_Channel + 28) -= Extra_Commands_Queue;

	using Send_Network_Message_Type = void(__thiscall**)(void* Network_Channel, void* Message, void* Unknown_Parameter_1, void* Unknown_Parameter_2);

	(*Send_Network_Message_Type(*(unsigned __int32*)Network_Channel + 164))(Network_Channel, &Message, nullptr, nullptr);
}