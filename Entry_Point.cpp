#include <Windows.h>

#include <TlHelp32.h>

#include <cstdio>

#define Bits_32

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

void* Engine_Module;

#include "Extended_Interface.hpp"

void* Client_Module;

#include "Post_Network_Data_Received.hpp"

#include "Interpolate.hpp"

#include <unordered_set>

#include "Estimate_Velocity.hpp"

#include "Spawn_Grenade.hpp"

#include "Run_Prediction.hpp"

#include "Run_Command.hpp"

#include "Play_Footstep_Sound.hpp"

#include <algorithm>

#include "Finish_Move.hpp"

#include "Item_Post_Frame.hpp"

#include "Perform_Trace.hpp"

#include "Perform_Shove_Trace.hpp"

#include "Read_Packets.hpp"

#include "Move.hpp"

#include <vector>

#include <unordered_map>

#include "Copy_Command.hpp"

#include "Calculate_View.hpp"

#include "Draw_Effect.hpp"

#include "Write_Texture.hpp"

#include "Paint.hpp"

#include "Get_Glow_Color.hpp"

#include "Draw_Crosshair.hpp"

__int32 __stdcall DllMain(HMODULE This_Module, unsigned __int32 Call_Reason, void* Reserved)
{
	if (Call_Reason == DLL_PROCESS_DETACH)
	{
		__fastfail(EXIT_SUCCESS);
	}
	else
	{
		if (Call_Reason == DLL_PROCESS_ATTACH)
		{
			if (GetModuleHandleW(L"left4dead2.exe") == nullptr)
			{
				void* Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

				PROCESSENTRY32W Snapshot_Entry;

				Snapshot_Entry.dwSize = sizeof(Snapshot_Entry);

				Traverse_Snapshot_Label:
				{
					if (Process32NextW(Snapshot, &Snapshot_Entry) == 0)
					{
						return 1;
					}

					if (wcscmp(Snapshot_Entry.szExeFile, L"left4dead2.exe") != 0)
					{
						goto Traverse_Snapshot_Label;
					}
				}

				void* Process = OpenProcess(PROCESS_ALL_ACCESS, 0, Snapshot_Entry.th32ProcessID);

				void* Remote_Path = VirtualAllocEx(Process, nullptr, 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

				wchar_t Local_Path[MAX_PATH];

				GetModuleFileNameW(This_Module, Local_Path, sizeof(Local_Path));

				WriteProcessMemory(Process, Remote_Path, Local_Path, sizeof(Local_Path), nullptr);

				WaitForSingleObject(CreateRemoteThread(Process, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, Remote_Path, 0, nullptr), INFINITE);

				VirtualFreeEx(Process, Remote_Path, 0, MEM_RELEASE);
			}
			else
			{
				Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)LoadLibraryW(L"vaudio_speex.dll") + 9440), 1, 195);

				AllocConsole();

				SetConsoleTitleW(L"Storm");

				_wfreopen(L"CONOUT$", L"w", stdout);

				SetConsoleOutputCP(65001);

				HANDLE Standard_Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

				CONSOLE_FONT_INFOEX Console_Font_Information;

				Console_Font_Information.cbSize = sizeof(CONSOLE_FONT_INFOEX);

				Console_Font_Information.nFont = 0;

				Console_Font_Information.dwFontSize.X = 0;

				Console_Font_Information.dwFontSize.Y = 12;

				Console_Font_Information.FontFamily = FF_DONTCARE;

				Console_Font_Information.FontWeight = FW_NORMAL;

				wcscpy(Console_Font_Information.FaceName, L"Terminal");

				SetCurrentConsoleFontEx(Standard_Output_Handle, 0, &Console_Font_Information);

				CONSOLE_CURSOR_INFO Console_Cursor_Information;

				Console_Cursor_Information.bVisible = 0;

				Console_Cursor_Information.dwSize = sizeof(Console_Cursor_Information);

				SetConsoleTextAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);

				SetConsoleCursorInfo(Standard_Output_Handle, &Console_Cursor_Information);

				CONSOLE_SCREEN_BUFFER_INFO Console_Screen_Buffer_Information;

				GetConsoleScreenBufferInfo(Standard_Output_Handle, &Console_Screen_Buffer_Information);

				COORD Top_Left =
				{
					0,

					0
				};

				DWORD Characters_Written_Count;

				FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written_Count);

				Engine_Module = GetModuleHandleW(L"engine.dll");

				_putws(L"[ + ] Extend Interface");
				{
					Implement_Extended_Interface();
				}

				Client_Module = GetModuleHandleW(L"client.dll");

				//DEBUG
				{
					*(__int32*)((unsigned __int32)Client_Module + 0x7B0528 + 0x14) &= ~0xA;
					*(__int32*)((unsigned __int32)Client_Module + 0x7807B8 + 0x14) &= ~0xA;
					*(__int32*)((unsigned __int32)Client_Module + 0x77E358 + 0x14) &= ~0xA;
				}

				_putws(L"[ + ] Events");
				{
					Redirection_Manager::Redirect_Function(Original_Post_Network_Data_Received_Caller, 0, (void*)((unsigned __int32)Client_Module + 1555088), 1, (void*)Redirected_Post_Network_Data_Received);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 316816), 1, 195);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Engine_Module + 521549), 1, 235);
				}

				_putws(L"[ + ] Interpolation");
				{
					Redirection_Manager::Redirect_Function(Original_Interpolate_Caller, 0, (void*)((unsigned __int32)Client_Module + 214256), 1, (void*)Redirected_Interpolate);
				}

				_putws(L"[ + ] Animations");
				{
					Redirection_Manager::Redirect_Function(Original_Estimate_Velocity_Caller, 0, (void*)((unsigned __int32)Client_Module + 311856), 1, (void*)Redirected_Estimate_Velocity);

					unsigned __int8 Maintain_Sequence_Transitions_Bytes[3] = { 194, 24, 0 };

					Byte_Manager::Copy_Bytes(1, (void*)((unsigned __int32)Client_Module + 245232), sizeof(Maintain_Sequence_Transitions_Bytes), Maintain_Sequence_Transitions_Bytes);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 3236851), 1, 15);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 3237030), 1, 15);
				}

				_putws(L"[ + ] Prediction");
				{
					static Prediction_Descriptor_Structure Original_Prediction_Descriptor;

					Prediction_Descriptor_Structure* Prediction_Descriptor = (Prediction_Descriptor_Structure*)((unsigned __int32)Client_Module + 7282444);

					Byte_Manager::Copy_Bytes(0, &Original_Prediction_Descriptor, sizeof(Prediction_Descriptor_Structure), Prediction_Descriptor);

					static Prediction_Field_Structure Prediction_Fields = { 1, (char*)"m_fMaxSpread", 3340, 1, { }, sizeof(float) };

					Prediction_Descriptor->Fields = &Prediction_Fields;

					Prediction_Descriptor->Size = sizeof(Prediction_Fields) / sizeof(Prediction_Field_Structure);

					Prediction_Descriptor->Parent = &Original_Prediction_Descriptor;

					Redirection_Manager::Redirect_Function(Original_Spawn_Grenade_Caller, 2, (void*)((unsigned __int32)Client_Module + 2227120), 1, (void*)Redirected_Spawn_Grenade);

					Redirection_Manager::Redirect_Function(Original_Run_Prediction_Caller, 0, (void*)((unsigned __int32)Engine_Module + 527584), 1, (void*)Redirected_Run_Prediction);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1557600), 1, 235);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1557511), 8, 144);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 2465971), 5, 144);

					Redirection_Manager::Redirect_Function(Original_Run_Command_Caller, 0, (void*)((unsigned __int32)Client_Module + 1553328), 1, (void*)Redirected_Run_Command);

					Redirection_Manager::Redirect_Function(Original_Play_Footstep_Sound_Caller, 0, (void*)((unsigned __int32)Client_Module + 978336), 1, (void*)Redirected_Play_Footstep_Sound);

					Redirection_Manager::Redirect_Function(Original_Finish_Move_Caller, 2, (void*)((unsigned __int32)Client_Module + 1553088), 1, (void*)Redirected_Finish_Move);

					Redirection_Manager::Redirect_Function(Original_Item_Post_Frame_Caller, 3, (void*)((unsigned __int32)Client_Module + 2535760), 1, (void*)Redirected_Item_Post_Frame);

					*(__int32*)((unsigned __int32)Original_Item_Post_Frame_Caller + 5) = (__int32)((unsigned __int32)Client_Module + 2438103) - (__int32)Original_Item_Post_Frame_Caller;

					Redirection_Manager::Redirect_Function(Original_Perform_Trace_Caller, 0, (void*)((unsigned __int32)Client_Module + 3086496), 1, (void*)Redirected_Perform_Trace);

					Original_Perform_Shove_Trace_Caller = (void*)((unsigned __int32)Client_Module + 3213879);

					Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 3213870), (void*)Redirected_Perform_Shove_Trace);
				}

				_putws(L"[ + ] Network");
				{
					Redirection_Manager::Redirect_Function(Original_Read_Packets_Caller, 0, (void*)((unsigned __int32)Engine_Module + 499120), 1, (void*)Redirected_Read_Packets);

					Redirection_Manager::Redirect_Function(Original_Move_Caller, 3, (void*)((unsigned __int32)Engine_Module + 512096), 1, (void*)Redirected_Move);
				}

				_putws(L"[ + ] Input");
				{
					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1250469), 3, 144);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 417204), 1, 235);

					Redirection_Manager::Redirect_Function(Original_Copy_Command_Caller, 0, (void*)((unsigned __int32)Client_Module + 1094448), 1, (void*)Redirected_Copy_Command);
				}

				_putws(L"[ + ] Effects");
				{
					Redirection_Manager::Redirect_Function(Original_Calculate_View_Caller, 0, (void*)((unsigned __int32)Client_Module + 132944), 1, (void*)Redirected_Calculate_View);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 133424), 1, 235);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 2874334), 1, 246);

					Redirection_Manager::Redirect_Function(Original_Draw_Effect_Caller, 0, (void*)((unsigned __int32)Client_Module + 1425744), 1, (void*)Redirected_Draw_Effect);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 1868093), 1, 52);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 2648346), 1, 216);

					*(void**)((unsigned __int32)Client_Module + 8106800) = (void*)((unsigned __int32)Client_Module + 955612);
				}

				_putws(L"[ + ] Paint");
				{
					Redirection_Manager::Redirect_Function(Original_Write_Texture_Caller, 0, (void*)((unsigned __int32)GetModuleHandleW(L"vguimatsurface.dll") + 100560), 1, (void*)Redirected_Write_Texture);

					Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 2906288), (void*)Redirected_Paint);

					Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 2455120), (void*)Redirected_Get_Glow_Color);

					Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 2300832), (void*)Redirected_Draw_Crosshair);

					Byte_Manager::Set_Bytes(1, (void*)((unsigned __int32)Client_Module + 2923737), 1, 235);

					Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 3111488), (void*)Redirected_Draw_Crosshair);
				}
			}
		}
	}

	return 1;
}