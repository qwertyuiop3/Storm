void* Original_Calculate_View_Caller;

void __thiscall Redirected_Calculate_View(void* Player, void* Unknown_Parameter_1, float* Angles, void* Unknown_Parameter_2)
{
	(decltype(&Redirected_Calculate_View)(Original_Calculate_View_Caller))(Player, Unknown_Parameter_1, Angles, Unknown_Parameter_2);

	using Get_Eye_Angles_Type = float*(__thiscall*)(void* Entity);

	Byte_Manager::Copy_Bytes(0, Angles, sizeof(float[3]), Get_Eye_Angles_Type((unsigned __int32)Client_Module + 2236960)(Player));
}