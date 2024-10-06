float Update_Animation_Time;

__int8 Update_Animation_Type;

void __cdecl Redirected_Update_Animations()
{
    Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7096744);

    float Previous_Current_Time = Global_Variables->Current_Time;

    Global_Variables->Current_Time = Update_Animation_Time;

    float Previous_Frame_Time = Global_Variables->Frame_Time;

    Global_Variables->Frame_Time = Global_Variables->Interval_Per_Tick * Update_Animation_Type;

    __int32 Entity_Number = 0;

    Traverse_Animation_List_Label:
    {
        if (Entity_Number != *(__int32*)((unsigned __int32)Client_Module + 7479624))
        {
            void* Animation_List = *(void**)((unsigned __int32)Client_Module + 7479612);

            if ((*(__int8*)((unsigned __int32)Animation_List + 8 * Entity_Number + 4) & 1) != 0)
            {
                void* Entity = *(void**)((unsigned __int32)Animation_List + 8 * Entity_Number);

                *(float*)((unsigned __int32)Entity + 328) = Update_Animation_Time - Global_Variables->Frame_Time;

                using Update_Animation_Type = void(__thiscall**)(void* Entity);

                (*Update_Animation_Type(*(unsigned __int32*)Entity + 808))(Entity);
            }

            Entity_Number += 1;

            goto Traverse_Animation_List_Label;
        }
    }

    Global_Variables->Frame_Time = Previous_Frame_Time;

    Global_Variables->Current_Time = Previous_Current_Time;
}