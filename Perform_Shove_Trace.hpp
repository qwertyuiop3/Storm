void __thiscall Perform_Shove_Trace(void* Stack)
{
	if (*(void**)((unsigned __int32)Stack + 332) == Perform_Trace_Target)
	{
		Perform_Trace_Damage = 1.f;
	}
}

void* Original_Perform_Shove_Trace_Caller;

__attribute__((naked)) void Redirected_Perform_Shove_Trace()
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