void* Perform_Trace_Target;

float Vector_Normalize(float* Vector)
{
	using Vector_Normalize_Type = float(__thiscall*)(float* Vector);

	return Vector_Normalize_Type((unsigned __int32)Client_Module + 3536176)(Vector);
};

void Angle_Vectors(float* Angles, float* Forward, float* Right, float* Up)
{
	using Angle_Vectors_Type = void(__cdecl*)(float* Angles, float* Forward, float* Right, float* Up);

	Angle_Vectors_Type((unsigned __int32)Client_Module + 3539376)(Angles, Forward, Right, Up);
};

float Perform_Trace_Damage;

void __thiscall Perform_Trace(void* Stack)
{
	void* Entity = *(void**)((unsigned __int32)Stack + 312);

	if (Interface_Penetrate_Teammates.Integer == 0)
	{
		if (Get_Identifier(Entity, 0, 0) == 232)
		{
			void* Local_Player = *(void**)((unsigned __int32)Client_Module + 7498712);

			if (*(__int32*)((unsigned __int32)Entity + 228) == *(__int32*)((unsigned __int32)Local_Player + 228))
			{
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
			if (Interface_Penetration_Damage.Integer == 0)
			{
				Perform_Trace_Damage = 1;
			}
			else
			{
				float* Start = (float*)((unsigned __int32)Stack + 236);

				float Distance = __builtin_sqrtf(__builtin_powf(End[0] - Start[0], 2) + __builtin_powf(End[1] - Start[1], 2) + __builtin_powf(End[2] - Start[2], 2));

				float Damage;

				static void* Calculate_Damage = (void*)((unsigned __int32)GetModuleHandleW(L"server.dll") + 3950416);
				{
					asm("pushal"); //temporary. just in case
					asm("movl %0, %%esi" : : "m"(Weapon_Data) : "esi");
					asm("subl $16, %esp");
					asm("movss %0, %%xmm0" : : "m"(Distance) : "esp");
					asm("movdqu %xmm0, (%esp)");
					asm("calll *%0" : : "m"(Calculate_Damage));
					asm("movd %%xmm0, %0" : "=m"(Damage));
					asm("addl $16, %esp");
					asm("popal");
				}

				__int32 Identifier = Get_Identifier(Entity, 1, 0);

				auto Apply_Difficulty_Scaling = [&]() -> void
				{
					using Get_Difficulty_Type = __int32(__cdecl*)();

					float Multipliers[3] = { 0.8f, 0.7f, 0.6f };

					Damage *= Multipliers[Get_Difficulty_Type((unsigned __int32)Client_Module + 2650448)()];
				};

				__int32 Bullet_Type = *(__int32*)((unsigned __int32)Weapon_Data + 2128);

				__int8 Is_Shotgun = (Bullet_Type ^ 12) % 7 == 4;

				//should make sure it's not mutation8, mutation12, realism
				auto Apply_Shotgun_Scaling = [&]() -> void
				{
					if (Is_Shotgun == 1)
					{
						using Compute_Bounds_Type = void(__thiscall*)(void* Collision, float* Start, float* Bounds);

						using Get_Center_Type = float*(__thiscall*)(void* Entity);

						void* Local_Player = *(void**)Trace_Information;

						float Bounds[3];

						Compute_Bounds_Type((unsigned __int32)Client_Module + 878528)((void*)((unsigned __int32)Entity + 540), Get_Center_Type((unsigned __int32)Client_Module + 114400)(Local_Player), Bounds);

						using Calculate_Distance_Type = float(__thiscall*)(void* Collision, float* Bounds);

						float Distance = Calculate_Distance_Type((unsigned __int32)Client_Module + 878608)((void*)((unsigned __int32)Local_Player + 540), Bounds);

						if (Distance < 100)
						{
							Damage += (4.f * Damage) * __builtin_powf(1.f - Distance / 100.f, 2);
						}
					}
				};

				if (Identifier == 277)
				{
					//nb_delete_all;z_spawn witch
					if (Group != 1)
					{
						Apply_Difficulty_Scaling();
					}

					Apply_Shotgun_Scaling();
				}
				else
				{
					if (Identifier == 264)
					{
						//nb_delete_all;ent_create commentary_zombie_spawner; ent_fire commentary_zombie_spawner spawnzombie common_male_fallen_survivor; ent_fire commentary_zombie_spawner kill
						//id: 14
						//nb_delete_all;ent_create commentary_zombie_spawner; ent_fire commentary_zombie_spawner spawnzombie common_male_jimmy; ent_fire commentary_zombie_spawner kill
						//id: 17
						if (Bullet_Type == 6)
						{
							Damage = __builtin_inff();
						}
						else
						{
							if (Upgrade_Type == 1)
							{
								Damage = __builtin_inff();
							}
							else
							{
								Apply_Shotgun_Scaling();

								__int8 Is_Sniper_Rifle = Bullet_Type == 9 || Bullet_Type == 10;

								if (Group == 1)
								{
									if (Gender == 14)
									{
										auto Is_Neutral = [&]() -> __int8
										{
											__int32 Sequence_Activity = *(__int32*)((unsigned __int32)Entity + 4688);

											unsigned __int32 Absolute_Sequence_Activity = Sequence_Activity - 563;

											if (Absolute_Sequence_Activity <= 29)
											{
												return (536870929 & (1 << (Absolute_Sequence_Activity & 31))) != 0;
											}

											return (Sequence_Activity == 600) + (Sequence_Activity == 648);
										};

										if (Is_Neutral() == 1)
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

									if (Is_Shotgun * (Group == 3) == 1)
									{
										Damage = __builtin_inff();
									}
									else
									{
										Apply_Difficulty_Scaling();

										if (Bullet_Type == 2 || Is_Sniper_Rifle == 1)
										{
											if (Gender == 14)
											{
												Damage = 450;
											}
											else
											{
												Damage = __builtin_inff();
											}
										}
										else
										{
											if (Bullet_Type >= 6)
											{
												if ((Bullet_Type - 3) % 4 > 1)
												{
													Damage = __builtin_inff();
												}
											}
										}
									}
								}
							}
						}
					}
					else
					{
						if (Identifier != 13)
						{
							//nb_delete_all;z_spawn tank
							if (Identifier + Bullet_Type == 284)
							{
								Damage *= 0.85f;
							}

							if (Upgrade_Type != 1)
							{
								if (Identifier != 276)
								{
									Damage *= 1.f + 3.f * (Group == 1) + 0.25f * ((Group == 3) + -(Group == 7));

									if (Identifier * Group == 270)
									{
										if (*(void**)((unsigned __int32)Entity + 8040) != INVALID_HANDLE_VALUE)
										{
											Damage = __builtin_inff();
										}
									}
								}
							}

							Damage = (__int32)(Damage + 1.f * (Damage < 1));
						}
					}
				}

				if (Is_Shotgun * Upgrade_Type == 1)
				{
					Damage *= *(__int32*)((unsigned __int32)Weapon_Data + 2520);
				}

				wprintf(L"[%d] type %d, %d\n", Group, Bullet_Type, Upgrade_Type);

				Perform_Trace_Damage += Damage;
			}
		};

		if (Upgrade_Type + Gender == 17)
		{
			float Inflictor_Direction[3];

			using Get_Center_Type = float*(__thiscall*)(void* Entity);

			float* Start = Get_Center_Type((unsigned __int32)Client_Module + 114400)(*(void**)Trace_Information);

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

			if (Inflictor_Direction[0] * Victim_Direction[0] + Inflictor_Direction[1] * Victim_Direction[1] + Inflictor_Direction[2] * Victim_Direction[2] >= 0)
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

void __declspec(naked) Redirected_Perform_Trace()
{
	asm("pushal");
	asm("movl %esp, %ecx");
	asm("calll %0" : : "m"(Perform_Trace));
	asm("popal");
	asm("jmpl *%0" : : "m"(Original_Perform_Trace_Caller));
}