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
		if (Interface_Aim_Intersection.Integer == 0)
		{
			if (*(__int32*)((unsigned __int32)Stack + 304) != 1)
			{
				return;
			}
		}

		void* Trace_Information = *(void**)((unsigned __int32)Stack + 36);

		if ((*(__int32*)((unsigned __int32)Trace_Information + 36) & 255) + *(__int32*)((unsigned __int32)Entity + 52) == 17)
		{
			float Inflictor_Direction[3];

			float* End = (float*)((unsigned __int32)Stack + 248);

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
	asm("pusha");
	asm("mov %esp, %ecx");
	asm("calll %0" : : "m"(Perform_Trace));
	asm("popa");
	asm("jmp *%0" : : "m"(Original_Perform_Trace_Caller));
}