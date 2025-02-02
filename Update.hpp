void* Original_Update_Caller;

void __thiscall Redirected_Update(void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, __int32 Incoming_Sequence_Number, int Outgoing_Sequence_Number)
{
	Consistent_Time = Outgoing_Sequence_Number - Incoming_Sequence_Number > 150;

	(decltype(&Redirected_Update)(Original_Update_Caller))(Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Incoming_Sequence_Number, Incoming_Sequence_Number + (Outgoing_Sequence_Number - Incoming_Sequence_Number) % 150);
}