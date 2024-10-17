__int32 Get_Identifier(void* Entity, __int8 Raw, __int8 Equipment)
{
	using Get_Identifier_Type = void*(__cdecl**)();

	__int32 Identifier = *(__int32*)((unsigned __int32)(*Get_Identifier_Type(*(unsigned __int32*)((unsigned __int32)Entity + 8) + 4))() + 20);

	if (Raw == 1)
	{
		return Identifier;
	}

	static std::unordered_set<__int32> Targets =
	{
		0,

		13,

		99,

		232,

		263,

		264,

		265,

		270,

		272,

		275,

		276,

		277
	};

	if (Targets.contains(Identifier) == 1)
	{
		__int8 Valid = 0;

		if (Identifier == 13)
		{
			*(__int32*)((unsigned __int32)Entity + 228) = 1;

			Valid = *(__int8*)((unsigned __int32)Entity + 324) == 5;
		}
		else
		{
			if (*(__int8*)((unsigned __int32)Entity + 221) == 0)
			{
				if ((*(__int32*)((unsigned __int32)Entity + 572) - 131088 & 255) == 0)
				{
					using Get_Sequence_Name_Type = char*(__thiscall*)(void* Entity, __int32 Sequence);

					if (__builtin_strstr(Get_Sequence_Name_Type((unsigned __int32)Client_Module + 203392)(Entity, *(__int32*)((unsigned __int32)Entity + 2212)), "eath") == nullptr)
					{
						Valid = 1;
					}
				}
			}
		}

		if (Valid == 1)
		{
			if (Identifier * (*(__int32*)((unsigned __int32)Entity + 228) == 3) == 232)
			{
				static std::unordered_map<__int32, __int32> Translators =
				{
					{ 1, 270 },

					{ 2, 0 },

					{ 3, 263 },

					{ 4, 272 },

					{ 5, 265 },

					{ 6, 99 },

					{ 8, 276 }
				};

				Identifier = Translators[*(__int32*)((unsigned __int32)Entity + 7312)];
			}

			return (Identifier - 232) % 43 ? Identifier : 232;
		}
	}
	else
	{
		if (Equipment == 1)
		{
			static std::unordered_set<__int32> Equipment_List =
			{
				73,

				105,

				109,

				121,

				256,

				260
			};

			if (Equipment_List.contains(Identifier) == 1)
			{
				if (Identifier == 260)
				{
					static std::unordered_map<__int32, __int32> Translators =
					{
						{ 12, 73 },

						{ 15, 121 },

						{ 23, 105 },

						{ 24, 109 }
					};

					Identifier = Translators[*(__int32*)((unsigned __int32)Entity + 2392)];
				}

				if (Identifier != 0)
				{
					if (*(void**)((unsigned __int32)Entity + 312) == INVALID_HANDLE_VALUE)
					{
						return -Identifier;
					}
				}
			}
		}
	}

	return -1;
}

void* Original_Estimate_Velocity_Caller;

void __thiscall Redirected_Estimate_Velocity(void* Entity, float* Velocity)
{
	static std::unordered_set<__int32> Invalids =
	{
		264,

		277
	};

	if (Invalids.contains(Get_Identifier(Entity, 1, 0)) == 1)
	{
		(decltype(&Redirected_Estimate_Velocity)(Original_Estimate_Velocity_Caller))(Entity, Velocity);
	}
	else
	{
		using Calculate_Velocity_Type = void(__thiscall*)(void* Entity);

		Calculate_Velocity_Type((unsigned __int32)Client_Module + 290704)(Entity);

		Velocity[0] = *(float*)((unsigned __int32)Entity + 136);

		Velocity[1] = *(float*)((unsigned __int32)Entity + 140);

		Velocity[2] = *(float*)((unsigned __int32)Entity + 144);
	}
}