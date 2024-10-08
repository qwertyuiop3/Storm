struct Interface_Structure
{
	__int8 Additional_Bytes_1[36];

	char* String;

	__int8 Additional_Bytes_2[4];

	float Floating_Point;

	__int32 Integer;

	__int8 Additional_Bytes_3[20];
};

Interface_Structure Interface_Extra_Commands;

Interface_Structure Interface_Interpolate_Extra_Commands;

Interface_Structure Interface_Target_On_Simulation;

Interface_Structure Interface_Riot_Deprioritize;

Interface_Structure Interface_Penetrate_Teammates;

Interface_Structure Interface_Aim_Intersection;

Interface_Structure Interface_Equipment_Distance;

Interface_Structure Interface_Storm_Rotation_Radius;

Interface_Structure Interface_Storm_Radius;

Interface_Structure Interface_Storm_Segments;

Interface_Structure Interface_Storm_Iterations;

Interface_Structure Interface_Storm_Speed;

void Implement_Extended_Interface()
{
	auto Create_Console_Interface = [](Interface_Structure* Interface, char* Name, char* Value, void* Handler)
	{
		using Create_Console_Variable_Type = void(__thiscall*)(Interface_Structure* Interface, char* Name, char* Value, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Handler);

		Create_Console_Variable_Type((unsigned __int32)Engine_Module + 2636656)(Interface, Name, Value, nullptr, nullptr, Handler);

		*(__int32*)((unsigned __int32)Interface + 20) &= ~10;

		wprintf(L"[ + ] %hs -> %p\n", Name, Interface);
	};

	#define Pointer_Name(Interface) &Interface, (char*)#Interface + 10

	Create_Console_Interface(Pointer_Name(Interface_Extra_Commands), (char*)"4", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Interpolate_Extra_Commands), (char*)"1", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Target_On_Simulation), (char*)"0", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Riot_Deprioritize), (char*)"0", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Penetrate_Teammates), (char*)"0", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Aim_Intersection), (char*)"1", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Equipment_Distance), (char*)"2048", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Storm_Rotation_Radius), (char*)"24", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Storm_Radius), (char*)"8", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Storm_Segments), (char*)"12", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Storm_Iterations), (char*)"16", nullptr);

	Create_Console_Interface(Pointer_Name(Interface_Storm_Speed), (char*)"512", nullptr);
}