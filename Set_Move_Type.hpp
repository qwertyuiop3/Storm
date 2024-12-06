void Redirected_Set_Move_Type(void* Input, void* Output)
{
	if (*(__int8*)((unsigned __int32)Output + 324) == 0)
	{
		*(float*)((unsigned __int32)Output + 472) = *(float*)((unsigned __int32)Output + 336);
	}

	*(__int8*)((unsigned __int32)Output + 324) = *(__int8*)((unsigned __int32)Input + 4);

	*(__int8*)((unsigned __int32)Output + 325) = 0;
}