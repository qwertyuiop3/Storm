void* Original_Calculate_View_Caller;

void __thiscall Redirected_Calculate_View(void* Player, void* Unknown_Parameter_1, float* Angles, void* Unknown_Parameter_2)
{
	(decltype(&Redirected_Calculate_View)(Original_Calculate_View_Caller))(Player, Unknown_Parameter_1, Angles, Unknown_Parameter_2);

	Byte_Manager::Copy_Bytes(1, Angles, sizeof(float[3]), (float*)((unsigned __int32)Player + 4996));
}