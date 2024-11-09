void Redirected_Draw_Crosshair()
{
	static float Rotation_Angle;

	auto Draw_Storm = [&](__int32 X, __int32 Y, __int32 Additional_Rotation_Angle)
	{
		using Set_Color_Type = void(__thiscall**)(void* Surface, unsigned __int8 Red, unsigned __int8 Green, unsigned __int8 Blue, unsigned __int8 Alpha);

		void* Surface = *(void**)((unsigned __int32)Client_Module + 8960244);

		(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 0, 0, 0, 255);

		using Draw_Circle_Type = void(__thiscall**)(void* Surface, __int32 X, __int32 Y, __int32 Radius, __int32 Segments);

		X += Interface_Storm_Rotation_Radius.Integer * __builtin_cosf(__builtin_remainderf(Rotation_Angle + Additional_Rotation_Angle, 360.f) * 3.1415927f / 180.f);

		Y += Interface_Storm_Rotation_Radius.Integer * __builtin_sinf(__builtin_remainderf(Rotation_Angle + Additional_Rotation_Angle, 360.f) * 3.1415927f / 180.f);

		(*Draw_Circle_Type(*(unsigned __int32*)Surface + 384))(Surface, X - 1, Y, Interface_Storm_Radius.Integer, Interface_Storm_Segments.Integer);

		(*Draw_Circle_Type(*(unsigned __int32*)Surface + 384))(Surface, X, Y - 1, Interface_Storm_Radius.Integer, Interface_Storm_Segments.Integer);

		(*Draw_Circle_Type(*(unsigned __int32*)Surface + 384))(Surface, X + 1, Y, Interface_Storm_Radius.Integer, Interface_Storm_Segments.Integer);

		(*Draw_Circle_Type(*(unsigned __int32*)Surface + 384))(Surface, X, Y + 1, Interface_Storm_Radius.Integer, Interface_Storm_Segments.Integer);

		(*Draw_Circle_Type(*(unsigned __int32*)Surface + 384))(Surface, X - 1, Y - 1, Interface_Storm_Radius.Integer, Interface_Storm_Segments.Integer);

		(*Draw_Circle_Type(*(unsigned __int32*)Surface + 384))(Surface, X + 1, Y - 1, Interface_Storm_Radius.Integer, Interface_Storm_Segments.Integer);

		(*Draw_Circle_Type(*(unsigned __int32*)Surface + 384))(Surface, X - 1, Y + 1, Interface_Storm_Radius.Integer, Interface_Storm_Segments.Integer);

		(*Draw_Circle_Type(*(unsigned __int32*)Surface + 384))(Surface, X + 1, Y + 1, Interface_Storm_Radius.Integer, Interface_Storm_Segments.Integer);

		(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 0, 128, 255, 255);

		(*Draw_Circle_Type(*(unsigned __int32*)Surface + 384))(Surface, X, Y, Interface_Storm_Radius.Integer, Interface_Storm_Segments.Integer);
	};

	__int32 Storm_Number = 0;

	using Get_Screen_Size_Type = __int32(__cdecl*)(__int32* Width, __int32* Height);

	__int32 Screen_Width;

	__int32 Screen_Height;

	Get_Screen_Size_Type((unsigned __int32)Client_Module + 1780352)(&Screen_Width, &Screen_Height);

	Screen_Width /= 2;

	Screen_Height /= 2;

	Draw_Storm_Label:
	{
		if (Storm_Number < Interface_Storm_Iterations.Integer)
		{
			Draw_Storm(Screen_Width, Screen_Height, Storm_Number * 360 / Interface_Storm_Iterations.Integer);

			Storm_Number += 1;

			goto Draw_Storm_Label;
		}
	}

	Rotation_Angle = __builtin_remainderf(Rotation_Angle + (*(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7096744))->Frame_Time * Interface_Storm_Speed.Integer, 360.f);
}