void __thiscall Perform_Shove_Trace(void* Stack)
{
	void* Entity = *(void**)((unsigned __int32)Stack - 276);

	if (Entity == (void*)((unsigned __int32)Perform_Trace_Target ^ 1))
	{
		Perform_Trace_Target = Entity;
	}
}

void* Original_Perform_Shove_Trace_Caller;

void __declspec(naked) Redirected_Perform_Shove_Trace()
{
	asm("lea -304(%ebp), %eax");
	asm("push %eax");
	asm("call *%edx");
	asm("pusha");
	asm("mov %esp, %ecx");
	asm("calll %0" : : "m"(Perform_Shove_Trace));
	asm("popa");
	asm("jmp *%0" : : "m"(Original_Perform_Shove_Trace_Caller));
}