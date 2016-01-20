;;==================================================================================;;
;;																					;;	
;;		interrupt.s - interrupt handlers for isr0 - 32								;;
;;																					;;
;;==================================================================================;;

%macro ISR_NOERRCODE 1		;define a macro taking one parameter

	[GLOBAL isr%1]			;%1 accesses the first parameter.
	isr%1:
		cli					; disable interrupts
		push byte 0			; dummy error code 0
		push byte %1		
		jmp isr_common_stub	
%endmacro

%macro ISR_ERRCODE 1		; define a macro taking one parameter	
	[GLOBAL isr%1]			
	isr%1:
		cli					; disable interrupts
		push byte %1		; push the actual error code?
		jmp isr_common_stub
%endmacro

;; This is hardware defined so just has to be here 
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

;in isr.c
[EXTERN isr_handler]

;; ISR stub, save processor state, sets up for kernel mode segments, calls fault handler in C
;; then restores the stack frame

isr_common_stub:
	pusha					;pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

	mov ax, ds				; Lower 16-bits of eax = ds.
	push eax				; save the data segment descriptor

	mov ax, 0x10			; load the kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call isr_handler

	pop eax					; reload the original data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	popa					; pops all registers
	add esp, 8				; Clean up the pushed error code and pushed ISR number
	sti						; set interrupt flag - RE-ENABLE interrupts
	iret					; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
