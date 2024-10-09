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
	asm("leal -304(%ebp), %eax");
	asm("pushl %eax");
	asm("calll *%edx");
	asm("pushal");
	asm("movl %esp, %ecx");
	asm("calll %0" : : "m"(Perform_Shove_Trace));
	asm("popal");
	asm("jmpl *%0" : : "m"(Original_Perform_Shove_Trace_Caller));
}