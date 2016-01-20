;=================================================================;
;								  								  ;
;		asm_lgdt.s - Initialization procedure for loading		  ;
;			         the global segment descriptor table		  ; 
;		@author 	www.jamesmolloy.co.uk 
;			                             		  				  ;
;=================================================================;

[GLOBAL gdt_flush]
[GLOBAL idt_flush]

;; _init_gdt:
;;	as	0x00 - first byte remains NULL 
;;	1	0x08 - kernel code segment - 0x00000000 to 0xFFFFFFFF - RW - PL0
;;	2	0x10 - kernel data segment - 0x00000000 to 0xFFFFFFFF - RW - PL0

gdt_flush:
	mov eax, [esp + 4]			; move the gdt struct param into eax
	lgdt [eax]					; load the gdt into the processor

	mov ax, 0x10				; 0x10 is the offset in the GDT to data seg
	mov ds, ax
	mov	es, ax
	mov fs, ax 
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush

.flush:
	ret							;now we have set cs to 0x08

idt_flush:
	mov eax, [esp + 4]			; Get the pointer to the IDT, passed as a parameter.
	lidt [eax]					; Load the IDT pointer.
	ret
