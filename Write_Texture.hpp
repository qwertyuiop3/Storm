void* Original_Write_Texture_Caller;

wchar_t Write_Character;

std::unordered_map<wchar_t, unsigned __int32[4]> Characters_Bounds;

void __thiscall Redirected_Write_Texture(void* Unknown_Parameter_1, void* Unknown_Parameter_2, unsigned __int32 Width, unsigned __int32 Height, void* Texture)
{
	(decltype(&Redirected_Write_Texture)(Original_Write_Texture_Caller))(Unknown_Parameter_1, Unknown_Parameter_2, Width, Height, Texture);

	if (Write_Character != 0)
	{
		unsigned __int32 X = 0;

		unsigned __int32 Offset_X = Width;

		unsigned __int32 Offset_Y = Height;

		unsigned __int32 Character_Width = 0;

		unsigned __int32 Character_Height = 0;

		Traverse_Horizontal_Label:
		{
			unsigned __int32 Y = 0;

			Traverse_Vertical_Label:
			{
				if (*(unsigned __int32*)((unsigned __int32)Texture + X * 4 + Y * 4 * Width) != 0)
				{
					Offset_X = min(Offset_X, X);

					Character_Width = max(Character_Width, X + 1);

					Offset_Y = min(Offset_Y, Y);

					Character_Height = max(Character_Height, Y + 1);
				}

				Y += 1;

				if (Y != Height)
				{
					goto Traverse_Vertical_Label;
				}
			}

			X += 1;

			if (X != Width)
			{
				goto Traverse_Horizontal_Label;
			}
		}

		unsigned __int32* Character_Bounds = Characters_Bounds[Write_Character];

		Character_Bounds[0] = Offset_X;

		Character_Bounds[1] = Character_Width - Offset_X;

		Character_Bounds[2] = Offset_Y;

		Character_Bounds[3] = Character_Height;
	}
}