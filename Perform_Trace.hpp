void* Perform_Trace_Target;

__declspec(noinline) float Calculate_Damage(void* Weapon_Data, float Distance)
{
	static void* Calculate_Damage = (void*)((unsigned __int32)GetModuleHandleW(L"server.dll") + 3950416);

	float Damage;

	asm("pushl %esi");
	asm("movl %0, %%esi" : : "m"(Weapon_Data));
	asm("subl $16, %esp");
	asm("movss %0, %%xmm0" : : "m"(Distance) : "esp");
	asm("movdqu %xmm0, (%esp)");
	asm("calll *%0" : : "m"(Calculate_Damage));
	asm("movd %%xmm0, %0" : "=m"(Damage));
	asm("addl $16, %esp");
	asm("popl %esi");

	return Damage;
}

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

	if (Entity == (void*)((unsigned __int32)Perform_Trace_Target ^ 1))
	{
		__int32 Group = *(__int32*)((unsigned __int32)Stack + 304);

		if (Interface_Aim_Intersection.Integer == 0)
		{
			if (Group != 1)
			{
				return;
			}
		}

		float* End = (float*)((unsigned __int32)Stack + 248);

		void* Trace_Information = *(void**)((unsigned __int32)Stack + 36);

		if (Interface_Penetration_Damage.Integer != 0) //that's very cutted version of actual function [*::TraceAttack]
		{
			float* Start = (float*)((unsigned __int32)Stack + 236);

			float Damage = Calculate_Damage(*(void**)((unsigned __int32)Trace_Information + 4), __builtin_sqrtf(__builtin_powf(End[0] - Start[0], 2) + __builtin_powf(End[1] - Start[1], 2) + __builtin_powf(End[2] - Start[2], 2)));
			
			__int32 Identifier = Get_Identifier(Entity, 1, 0);

			auto Apply_Difficulty_Scaling = [&]() -> void
			{
				using Get_Difficulty_Type = __int32(__cdecl*)();

				//z_non_head_damage_factor_* (non-replicated unfortunately)
				//assuming "z_use_next_difficulty_damage_factor" is "1" and "maxplayers" is not "1"
				float Multipliers[4] = { 0.8f, 0.7f, 0.6f, 1.f };

				Damage *= Multipliers[Get_Difficulty_Type((unsigned __int32)Client_Module + 2650448)()];
			};

			if (Identifier == 277) //special scaling used by witches
			{
				if (Group != 1)
				{
					Apply_Difficulty_Scaling();
				}
			}
			else
			{
				if (Identifier == 264) //special scaling used by common infected
				{
					if (Identifier * Group == 264) //these are killed instantly on headshot
					{
						Damage = FLT_MAX;
					}
					else
					{
						Apply_Difficulty_Scaling();

						//tbi: some guns are using special scaling (e.g. deagle)
					}
				}
				else //special scaling used by non-common infected
				{
					if (*(__int32*)((unsigned __int32)Trace_Information + 36) != -2139094974) //explosives are doing "radial" damage instead
					{
						if (Identifier != 276) //tanks aren't scaled
						{
							Damage *= 1.f + 3.f * (Group == 1) + 0.25f * (Group == 3) - 0.25f * (Group == 7); //or: 0.25f * ((Group == 3) + -(Group == 7))

							if (Identifier * Group == 270) //killed instantly on **hooked** headshot
							{
								if (*(void**)((unsigned __int32)Entity + 8040) != INVALID_HANDLE_VALUE)
								{
									Damage = FLT_MAX;
								}
							}
						}
					}

					Damage = (__int32)(Damage + 1.f * (Damage < 1)); //rounding isn't applied to common infected or witches. make sure damage isn't zero before rounding
				}

				//actual shotgun multiplications (z_shotgun_bonus_damage_multiplier, z_shotgun_bonus_damage_range) would require extraneous tracing... so they're not here for moment
			}

			wprintf(L"hitgroup %d -> damage %f\n", Group, Damage); //compared to 'picker' output (along with nb_stop 1), since it's unfinished feature

			if (Damage < Interface_Penetration_Damage.Floating_Point)
			{
				return;
			}
		}

		if ((*(__int32*)((unsigned __int32)Trace_Information + 36) & 255) + *(__int32*)((unsigned __int32)Entity + 52) == 17)
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
				Perform_Trace_Target = Entity;
			}
		}
		else
		{
			Perform_Trace_Target = Entity;
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