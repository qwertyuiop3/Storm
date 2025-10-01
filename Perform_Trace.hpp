void* Perform_Trace_Target;

float* Get_Center(void* Entity)
{
	using Get_Center_Type = float*(__thiscall*)(void* Entity);

	return Get_Center_Type((unsigned __int32)Client_Module + 114400)(Entity);
}

float Perform_Trace_Damage;

float Vector_Normalize(float* Vector)
{
	using Vector_Normalize_Type = float(__thiscall*)(float* Vector);

	return Vector_Normalize_Type((unsigned __int32)Client_Module + 3536192)(Vector);
};

void Angle_Vectors(float* Angles, float* Forward, float* Right, float* Up)
{
	using Angle_Vectors_Type = void(__cdecl*)(float* Angles, float* Forward, float* Right, float* Up);

	Angle_Vectors_Type((unsigned __int32)Client_Module + 3539392)(Angles, Forward, Right, Up);
};

void __thiscall Perform_Trace(void* Stack)
{
	void* Entity = *(void**)((unsigned __int32)Stack + 312);

	__int32 Identifier = Get_Identifier(Entity, 0, 0);

	if (Interface_Penetrate_Teammates.Integer == 0)
	{
		if (Identifier == 232)
		{
			void* Local_Player = *(void**)((unsigned __int32)Client_Module + 7498712);

			if (*(__int32*)((unsigned __int32)Entity + 228) == *(__int32*)((unsigned __int32)Local_Player + 228))
			{
				Perform_Trace_Target = nullptr;

				Perform_Trace_Damage = 0.f;

				return;
			}
		}
	}

	if (Entity == Perform_Trace_Target)
	{
		__int32 Group = *(__int32*)((unsigned __int32)Stack + 304);

		if (Interface_Aim_Intersection.Integer == 0)
		{
			if (Group != 1)
			{
				return;
			}
		}

		void* Trace_Information = *(void**)((unsigned __int32)Stack + 36);

		void* Weapon_Data = *(void**)((unsigned __int32)Trace_Information + 4);

		float* End = (float*)((unsigned __int32)Stack + 248);

		__int32 Upgrade_Type = (*(__int32*)((unsigned __int32)Trace_Information + 36) & 255) % 5;

		__int32 Gender = *(__int32*)((unsigned __int32)Entity + 52);

		auto Compute_Damage = [&]() -> void
		{
			if (Interface_Penetration_Damage.Floating_Point == 0.f)
			{
				Perform_Trace_Damage = 1.f;
			}
			else
			{
				float* Start = (float*)((unsigned __int32)Stack + 236);

				float Distance = __builtin_sqrtf(__builtin_powf(End[0] - Start[0], 2.f) + __builtin_powf(End[1] - Start[1], 2.f) + __builtin_powf(End[2] - Start[2], 2.f));

				float Damage;

				static void* Calculate_Damage = (void*)((unsigned __int32)GetModuleHandleW(L"server.dll") + 3950416);
				{
					asm("movl %0, %%esi" : : "m"(Weapon_Data) : "esi");
					asm("subl $16, %esp");
					asm("movss %0, %%xmm0" : : "m"(Distance) : "esp");
					asm("movdqu %xmm0, (%esp)");
					asm("calll *%0" : : "m"(Calculate_Damage) : "eax", "ecx", "edx");
					asm("movd %%xmm0, %0" : "=m"(Damage));
					asm("addl $16, %esp");
				}

				__int32 Bullet_Type = *(__int32*)((unsigned __int32)Weapon_Data + 2128);

				__int8 Is_Shotgun = (Bullet_Type ^ 12) % 7 == 4;

				if (Upgrade_Type * Is_Shotgun == 1)
				{
					Damage *= *(__int32*)((unsigned __int32)Weapon_Data + 2520);
				}

				auto Apply_Difficulty_Scaling = [&]() -> void
				{
					using Get_Difficulty_Type = __int32(__cdecl*)();

					static float Multipliers[3] = { 0.8f, 0.7f, 0.6f };

					Damage *= Multipliers[Get_Difficulty_Type((unsigned __int32)Client_Module + 2650448)()];
				};

				char* Mode = *(char**)((unsigned __int32)Client_Module + 8145092);

				__int8 Realism = Mode[0] == 'r';

				auto Apply_Shotgun_Scaling = [&]() -> void
				{
					if (Is_Shotgun == 1)
					{
						__int8 Hardcore = Realism;

						if (__builtin_strlen(Mode) > 8)
						{
							Hardcore = (Mode[8] == '8') + (Mode[9] == '2');
						}

						if (Hardcore == 0)
						{
							using Get_Bounds_Type = void(__thiscall*)(void* Collision, float* Start, float* Bounds);

							void* Local_Player = *(void**)Trace_Information;

							float Bounds[3];

							Get_Bounds_Type((unsigned __int32)Client_Module + 878528)((void*)((unsigned __int32)Entity + 540), Get_Center(Local_Player), Bounds);

							using Calculate_Distance_Type = float(__thiscall*)(void* Collision, float* Bounds);

							float Distance = Calculate_Distance_Type((unsigned __int32)Client_Module + 878608)((void*)((unsigned __int32)Local_Player + 540), Bounds);

							if (Distance < 100.f)
							{
								Damage += 4.f * Damage * __builtin_powf(1.f - Distance / 100.f, 2.f);
							}
						}
					}
				};

				if (Identifier == 13)
				{
					Damage *= *(float*)((unsigned __int32)Entity + 336) - *(float*)((unsigned __int32)Entity + 472) >= 0.5f;
				}
				else
				{
					if (Identifier == 264)
					{
						if ((Upgrade_Type == 1) + (Bullet_Type == 6) == 0)
						{
							Apply_Shotgun_Scaling();

							__int8 Is_Sniper_Rifle = Bullet_Type > 8;

							if (Group == 1)
							{
								if (Gender == 14)
								{
									static std::unordered_set<__int32> Neutrals = { 563, 567, 592, 600, 648 };

									if (Neutrals.contains(*(__int32*)((unsigned __int32)Entity + 4688)) == 1)
									{
										Damage = __builtin_inff();
									}
								}
								else
								{
									if (Gender != 17)
									{
										Damage = __builtin_inff();
									}
								}
							}
							else
							{
								if (Group * (Gender != 14) * (Gender != 17) * Is_Shotgun == 3)
								{
									Damage = __builtin_inff();
								}
								else
								{
									Apply_Difficulty_Scaling();

									if ((Bullet_Type == 2) + Is_Sniper_Rifle != 0)
									{
										if (Gender == 14)
										{
											if (Is_Sniper_Rifle * Realism == 0)
											{
												Damage = 450.f;
											}
										}
										else
										{
											Damage = __builtin_inff();
										}
									}
								}
							}
						}
						else
						{
							Damage = __builtin_inff();
						}
					}
					else
					{
						if (Identifier == 277)
						{
							if (Group != 1)
							{
								Apply_Difficulty_Scaling();
							}

							Apply_Shotgun_Scaling();
						}
						else
						{
							if (Identifier + Bullet_Type == 284)
							{
								Damage *= 0.85f;
							}

							if ((Identifier != 276) + (Upgrade_Type != 1) == 2)
							{
								static float Multipliers[8] = { 1.f, 4.f, 1.f, 1.25f, 1.f, 1.f, 0.75f, 0.75f };

								Damage *= min(Multipliers[Group], 4.f - 2.75f * Is_Shotgun);
							}

							__int32 Raw_Identifier = Get_Identifier(Entity, 1, 0);

							if (Raw_Identifier == 99)
							{
								if (*(__int32*)((unsigned __int32)Entity + 2212) == 5)
								{
									Damage *= 1.f / 3.f;
								}
							}
							else
							{
								if (Identifier * Group == 270)
								{
									if (*(void**)((unsigned __int32)Entity + 8040) != INVALID_HANDLE_VALUE)
									{
										if (Damage > 50.f)
										{
											__int8 Competitive = ('v' - Mode[0] ^ Mode[0] - 's') == 3;

											if (__builtin_strlen(Mode) > 8)
											{
												Competitive = Mode[9] == '8';
											}

											if (Competitive == 0)
											{
												Damage = __builtin_inff();
											}
										}
									}
								}
							}

							if (Damage != __builtin_inff())
							{
								Damage = (__int32)(Damage + 1.f * (Damage < 1.f));

								if (Raw_Identifier == 276)
								{
									if (__builtin_strstr(Get_Sequence_Name(Entity), "limb") != nullptr)
									{
										Damage = min(Damage, *(__int32*)((unsigned __int32)Entity + 236) - 1.f);
									}
								}
							}
						}
					}
				}

				Perform_Trace_Damage += Damage;
			}
		};

		if ((Upgrade_Type == 2) + (Gender == 15) == 2)
		{
			float Inflictor_Direction[3];

			float* Start = Get_Center(*(void**)Trace_Information);

			Inflictor_Direction[0] = End[0] - Start[0];

			Inflictor_Direction[1] = End[1] - Start[1];

			Inflictor_Direction[2] = End[2] - Start[2];

			Vector_Normalize(Inflictor_Direction);

			using Get_Attachment_Type = void(__thiscall*)(void* Entity, char* Attachment, float* Origin, float* Angle);

			float Origin[3];

			float Angle[3];

			Get_Attachment_Type((unsigned __int32)Client_Module + 178656)(Entity, (char*)"chest", Origin, Angle);

			float Victim_Direction[3];

			Angle_Vectors(Angle, Victim_Direction, nullptr, nullptr);

			if (Inflictor_Direction[0] * Victim_Direction[0] + Inflictor_Direction[1] * Victim_Direction[1] + Inflictor_Direction[2] * Victim_Direction[2] >= 0.f)
			{
				Compute_Damage();
			}
		}
		else
		{
			Compute_Damage();
		}
	}
}

void* Original_Perform_Trace_Caller;

__attribute__((naked)) void Redirected_Perform_Trace()
{
	asm("pushal");
	asm("movl %esp, %ecx");
	asm("calll %0" : : "m"(Perform_Trace));
	asm("popal");
	asm("jmpl *%0" : : "m"(Original_Perform_Trace_Caller));
}