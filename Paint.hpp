void __thiscall Redirected_Paint(void* Panel)
{
	using Set_Order_Type = void(__thiscall*)(void* Panel, __int32 Order);

	Set_Order_Type((unsigned __int32)Client_Module + 4082160)(Panel, -1);

	__int32 Entity_Number = 1;

	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 7498712);

	Sorted_Target_List.clear();

	Traverse_Entity_List_Label:
	{
		void* Entity = *(void**)((unsigned __int32)Client_Module + 7644532 + ((Entity_Number - 4097) << 4));

		if (Entity != nullptr)
		{
			if (Entity != Local_Player)
			{
				__int32 Identifier = Get_Identifier(Entity, 0, 1);

				if (Identifier != -1)
				{
					using Get_Origin_Type = float*(__thiscall*)(void* Entity);

					float* Local_Origin = Get_Origin_Type((unsigned __int32)Client_Module + 297584)(Local_Player);

					float* Entity_Origin = Get_Origin_Type((unsigned __int32)Client_Module + 297584)(Entity);

					Target_Structure Target =
					{
						__builtin_abs(Identifier),

						Entity,

						0,

						__builtin_powf(Local_Origin[0] - Entity_Origin[0], 2.f) + __builtin_powf(Local_Origin[1] - Entity_Origin[1], 2.f) + __builtin_powf(Local_Origin[2] - Entity_Origin[2], 2.f)
					};

					if (Identifier >= 0)
					{
						Sorted_Target_List.push_back(Target);
					}
					else
					{
						if (__builtin_sqrtf(Target.Distance) <= Interface_Equipment_Distance.Floating_Point)
						{
							Sorted_Target_List.push_back(Target);
						}
					}
				}
			}
		}

		if (Entity_Number != *(__int32*)((unsigned __int32)Client_Module + 7644568))
		{
			Entity_Number += 1;

			goto Traverse_Entity_List_Label;
		}
	}

	auto Target_List_Sort = [](Target_Structure& X, Target_Structure& Y) -> __int8
	{
		return X.Distance < Y.Distance;
	};

	std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort);

	size_t Target_Number = Sorted_Target_List.size() - 1;

	Traverse_Sorted_Target_List_Label:
	{
		if (Target_Number != -1)
		{
			Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

			float Bounds[4] = { __builtin_inff(), -__builtin_inff(), __builtin_inff(), -__builtin_inff()};

			auto Get_Bounds = [&]() -> __int8
			{
				float Bones[128][3][4];

				void* Hitbox_Set = Get_Hitbox_Set(Target, Bones, (*(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7096744))->Current_Time);

				if (Hitbox_Set != nullptr)
				{
					__int32 Hitbox_Number = 0;

					Get_Bounds_Label:
					{
						if (Hitbox_Number != *(__int32*)((unsigned __int32)Hitbox_Set + 4))
						{
							void* Hitbox = (void*)((unsigned __int32)Hitbox_Set + 12 + Hitbox_Number * 68);

							if (*(__int32*)Hitbox < sizeof(Bones) / sizeof(Bones[0]))
							{
								float* Hitbox_Minimum = (float*)((unsigned __int32)Hitbox + 8);

								float* Hitbox_Maximum = (float*)((unsigned __int32)Hitbox + 20);

								float Hitbox_Vertices[8][3];

								__int32 Axis_Number = 0;

								Initialize_Vertices_Label:
								{
									Hitbox_Vertices[0][Axis_Number] = Bones[*(__int32*)Hitbox][Axis_Number][0] * Hitbox_Minimum[0] + Bones[*(__int32*)Hitbox][Axis_Number][1] * Hitbox_Minimum[1] + Bones[*(__int32*)Hitbox][Axis_Number][2] * Hitbox_Minimum[2] + Bones[*(__int32*)Hitbox][Axis_Number][3];

									Hitbox_Vertices[1][Axis_Number] = Bones[*(__int32*)Hitbox][Axis_Number][0] * Hitbox_Maximum[0] + Bones[*(__int32*)Hitbox][Axis_Number][1] * Hitbox_Minimum[1] + Bones[*(__int32*)Hitbox][Axis_Number][2] * Hitbox_Minimum[2] + Bones[*(__int32*)Hitbox][Axis_Number][3];

									Hitbox_Vertices[2][Axis_Number] = Bones[*(__int32*)Hitbox][Axis_Number][0] * Hitbox_Minimum[0] + Bones[*(__int32*)Hitbox][Axis_Number][1] * Hitbox_Maximum[1] + Bones[*(__int32*)Hitbox][Axis_Number][2] * Hitbox_Minimum[2] + Bones[*(__int32*)Hitbox][Axis_Number][3];

									Hitbox_Vertices[3][Axis_Number] = Bones[*(__int32*)Hitbox][Axis_Number][0] * Hitbox_Minimum[0] + Bones[*(__int32*)Hitbox][Axis_Number][1] * Hitbox_Minimum[1] + Bones[*(__int32*)Hitbox][Axis_Number][2] * Hitbox_Maximum[2] + Bones[*(__int32*)Hitbox][Axis_Number][3];

									Hitbox_Vertices[4][Axis_Number] = Bones[*(__int32*)Hitbox][Axis_Number][0] * Hitbox_Maximum[0] + Bones[*(__int32*)Hitbox][Axis_Number][1] * Hitbox_Maximum[1] + Bones[*(__int32*)Hitbox][Axis_Number][2] * Hitbox_Minimum[2] + Bones[*(__int32*)Hitbox][Axis_Number][3];

									Hitbox_Vertices[5][Axis_Number] = Bones[*(__int32*)Hitbox][Axis_Number][0] * Hitbox_Maximum[0] + Bones[*(__int32*)Hitbox][Axis_Number][1] * Hitbox_Minimum[1] + Bones[*(__int32*)Hitbox][Axis_Number][2] * Hitbox_Maximum[2] + Bones[*(__int32*)Hitbox][Axis_Number][3];

									Hitbox_Vertices[6][Axis_Number] = Bones[*(__int32*)Hitbox][Axis_Number][0] * Hitbox_Minimum[0] + Bones[*(__int32*)Hitbox][Axis_Number][1] * Hitbox_Maximum[1] + Bones[*(__int32*)Hitbox][Axis_Number][2] * Hitbox_Maximum[2] + Bones[*(__int32*)Hitbox][Axis_Number][3];

									Hitbox_Vertices[7][Axis_Number] = Bones[*(__int32*)Hitbox][Axis_Number][0] * Hitbox_Maximum[0] + Bones[*(__int32*)Hitbox][Axis_Number][1] * Hitbox_Maximum[1] + Bones[*(__int32*)Hitbox][Axis_Number][2] * Hitbox_Maximum[2] + Bones[*(__int32*)Hitbox][Axis_Number][3];

									Axis_Number += 1;

									if (Axis_Number != sizeof(Hitbox_Vertices[0]) / sizeof(float))
									{
										goto Initialize_Vertices_Label;
									}
								}

								__int32 Vertex_Number = 0;

								Transform_Vertices_Label:
								{
									using Screen_Transform_Type = __int8(__cdecl*)(float* World, float* Screen);

									float Screen[3];

									if (Screen_Transform_Type((unsigned __int32)Client_Module + 1841648)(Hitbox_Vertices[Vertex_Number], Screen) == 0)
									{
										using Get_Screen_Size_Type = __int32(__cdecl*)();

										__int32 Screen_Width = Get_Screen_Size_Type((unsigned __int32)Client_Module + 738576)();

										__int32 Screen_Height = Get_Screen_Size_Type((unsigned __int32)Client_Module + 738544)();

										Screen[0] = Screen[0] / 2.f * Screen_Width + Screen_Width / 2.f;

										Screen[1] = -Screen[1] / 2.f * Screen_Height + Screen_Height / 2.f;

										Bounds[0] = min(Bounds[0], Screen[0]);

										Bounds[1] = max(Bounds[1], Screen[0]);

										Bounds[2] = min(Bounds[2], Screen[1]);

										Bounds[3] = max(Bounds[3], Screen[1]);
									}
									else
									{
										return 0;
									}

									Vertex_Number += 1;

									if (Vertex_Number != sizeof(Hitbox_Vertices) / sizeof(Hitbox_Vertices[0]))
									{
										goto Transform_Vertices_Label;
									}
								}

								Hitbox_Number += 1;

								goto Get_Bounds_Label;
							}
						}
					}

					Bounds[0] -= 2.f;

					Bounds[1] += 2.f;

					Bounds[2] -= 2.f;

					Bounds[3] += 2.f;
				}

				return __builtin_isfinite(Bounds[0]) * (Bounds[1] != 2.f) * (Bounds[3] != 2.f);
			};

			if (Get_Bounds() == 1)
			{
				void* Surface = *(void**)((unsigned __int32)Client_Module + 8960244);

				struct Paint_Data_Structure
				{
					unsigned __int8 Color[3];

					wchar_t* Name;
				};

				static std::unordered_map<__int32, Paint_Data_Structure> Paint_Data_List =
				{
					{ 0, { { 255, 128, 0 }, (wchar_t*)L"Boomer" } },

					{ 13, { { 0, 128, 255 }, (wchar_t*)L"Rock" } },

					{ 73, { { 255, 255, 255 }, (wchar_t*)L"Aid" } },

					{ 99, { { 255, 128, 0 }, (wchar_t*)L"Charger" } },

					{ 105, { { 255, 255, 255 }, (wchar_t*)L"Adrenaline" } },

					{ 109, { { 255, 255, 255 }, (wchar_t*)L"Defibrillator" } },

					{ 121, { { 255, 255, 255 }, (wchar_t*)L"Pain" } },

					{ 232, { { 0, 255, 0 } } },

					{ 256, { { 255, 255, 255 }, (wchar_t*)L"Ammo" } },

					{ 263, { { 255, 128, 0 }, (wchar_t*)L"Hunter" } },

					{ 264, { { 255, 0, 0 }, (wchar_t*)L"Infected" } },

					{ 265, { { 255, 128, 0 }, (wchar_t*)L"Jockey" } },

					{ 270, { { 255, 128, 0 }, (wchar_t*)L"Smoker" } },

					{ 272, { { 255, 128, 0 }, (wchar_t*)L"Spitter" } },

					{ 276, { { 0, 128, 255 }, (wchar_t*)L"Tank" } },

					{ 277, { { 0, 128, 255 }, (wchar_t*)L"Witch" } }
				};

				Paint_Data_Structure* Paint_Data = &Paint_Data_List[Target->Identifier];

				if (Target->Identifier == 232)
				{
					static wchar_t* Survivors[8] = { (wchar_t*)L"Nick", (wchar_t*)L"Rochelle", (wchar_t*)L"Coach", (wchar_t*)L"Ellis", (wchar_t*)L"Bill", (wchar_t*)L"Zoey", (wchar_t*)L"Louis", (wchar_t*)L"Francis" };

					Paint_Data->Name = Survivors[std::clamp(*(__int32*)((unsigned __int32)Target->Self + 7308), 0, 7) + 4 * (*(__int32*)((unsigned __int32)Client_Module + 8144624) == 1)];
				}

				__int8 Ghost = 0;

				if (*(__int32*)((unsigned __int32)Target->Self + 236) != 0)
				{
					Ghost = *(__int8*)((unsigned __int32)Target->Self + 7322);
				}

				auto Draw_Box = [&](__int32 From_X, __int32 From_Y, __int32 To_X, __int32 To_Y) -> void
				{
					using Set_Color_Type = void(__thiscall**)(void* Surface, unsigned __int8 Red, unsigned __int8 Green, unsigned __int8 Blue, unsigned __int8 Alpha);

					if (Ghost == 0)
					{
						(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, (__int32)(Paint_Data->Color[0] / 2.f + 0.5f), (__int32)(Paint_Data->Color[1] / 2.f + 0.5f), (__int32)(Paint_Data->Color[2] / 2.f + 0.5f), 128);
					}
					else
					{
						(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 64, 64, 64, 128);
					}

					using Draw_Filled_Rect_Type = void(__thiscall**)(void* Surface, __int32 From_X, __int32 From_Y, __int32 To_X, __int32 To_Y);

					(*Draw_Filled_Rect_Type(*(unsigned __int32*)Surface + 48))(Surface, From_X + 2, From_Y + 2, To_X - 2, To_Y - 2);

					(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 0, 0, 0, 255);

					using Draw_Rect_Type = void(__thiscall**)(void* Surface, __int32 From_X, __int32 From_Y, __int32 To_X, __int32 To_Y);

					(*Draw_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, From_X - 1, From_Y - 1, To_X + 1, To_Y + 1);

					(*Draw_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, From_X + 1, From_Y + 1, To_X - 1, To_Y - 1);

					if (Ghost == 0)
					{
						(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, Paint_Data->Color[0], Paint_Data->Color[1], Paint_Data->Color[2], 255);
					}
					else
					{
						(*Set_Color_Type(*(unsigned __int32*)Surface + 44))(Surface, 128, 128, 128, 255);
					}

					(*Draw_Rect_Type(*(unsigned __int32*)Surface + 56))(Surface, From_X, From_Y, To_X, To_Y);
				};

				Draw_Box(Bounds[0], Bounds[2], Bounds[1], Bounds[3]);

				using Draw_Text_Type = void(__cdecl*)(void* Font, __int32 X, __int32 Y, __int32 Red, __int32 Green, __int32 Blue, __int32 Alpha, wchar_t* Text);

				auto Create_Font = [&]() -> void*
				{
					using Create_Font_Type = void*(__thiscall**)(void* Surface);

					void* Font = (*Create_Font_Type(*(unsigned __int32*)Surface + 252))(Surface);

					using Setup_Font_Type = __int8(__thiscall**)(void* Surface, void* Font, char* Name, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3, void* Unknown_Parameter_4, __int32 Flags, void* Unknown_Parameter_5, void* Unknown_Parameter_6);

					(*Setup_Font_Type(*(unsigned __int32*)Surface + 256))(Surface, Font, (char*)"Fixedsys", nullptr, nullptr, nullptr, nullptr, 512, nullptr, nullptr);

					wchar_t Character = L' ';

					Calculate_Character_Bounds_Label:
					{
						wchar_t Text[2] = { Character };

						Write_Character = Text[0];

						Draw_Text_Type((unsigned __int32)Engine_Module + 2218736)(Font, 0, 0, 0, 0, 0, 0, Text);

						Write_Character = 0;

						if (Character != L'~')
						{
							Character += L'\1';

							goto Calculate_Character_Bounds_Label;
						}
					}

					return Font;
				};

				static void* Font = Create_Font();

				size_t Character_Number = 0;

				unsigned __int32 Width = 0;

				unsigned __int32 Height = 0;

				__int32 Offset_Y = 0;

				size_t Characters_Count = wcslen(Paint_Data->Name);

				Calculate_Text_Bounds_Label:
				{
					unsigned __int32* Character_Bounds = Characters_Bounds[Paint_Data->Name[Character_Number]];

					Width += Character_Bounds[1] + 1;

					Height = max(Height, Character_Bounds[3]);

					Offset_Y = max(Offset_Y, 3 - (__int32)Character_Bounds[2]);

					Character_Number += 1;

					if (Character_Number != Characters_Count)
					{
						goto Calculate_Text_Bounds_Label;
					}

					Draw_Box(Bounds[1] + 3, Bounds[2], Bounds[1] + 8 + Width, Bounds[2] + Height + Offset_Y + 3);

					Character_Number = 0;

					__int32 Offset_X = 0;

					Draw_Character_Label:
					{
						Character_Bounds = Characters_Bounds[Paint_Data->Name[Character_Number]];

						wchar_t Text[2] = { Paint_Data->Name[Character_Number] };

						if (Ghost == 0)
						{
							Draw_Text_Type((unsigned __int32)Engine_Module + 2218736)(Font, Bounds[1] + 7 + Offset_X - Character_Bounds[0], Bounds[2] + Offset_Y, Paint_Data->Color[0], Paint_Data->Color[1], Paint_Data->Color[2], 255, Text);
						}
						else
						{
							Draw_Text_Type((unsigned __int32)Engine_Module + 2218736)(Font, Bounds[1] + 7 + Offset_X - Character_Bounds[0], Bounds[2] + Offset_Y, 128, 128, 128, 255, Text);
						}

						Offset_X += Character_Bounds[1] + 1;

						Character_Number += 1;

						if (Character_Number != Characters_Count)
						{
							goto Draw_Character_Label;
						}
					}
				}
			}

			Target_Number -= 1;

			goto Traverse_Sorted_Target_List_Label;
		}
	}
}