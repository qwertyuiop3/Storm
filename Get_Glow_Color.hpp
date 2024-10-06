void* Original_Get_Glow_Color_Caller;

void __thiscall Redirected_Get_Glow_Color(void* Entity, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4)
{
	if (Get_Identifier(Entity, 0, 0) != 232)
	{
		(decltype(&Redirected_Get_Glow_Color)(Original_Get_Glow_Color_Caller))(Entity, Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4);
	}
}