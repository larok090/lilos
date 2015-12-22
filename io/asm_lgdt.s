;=================================================================;
;								  								  ;
;		asm_lgdt.s - Initialization procedure for loading		  ;
;			         the global segment descriptor table		  ; 
;			                             		  				  ;
;=================================================================;

[GLOBAL _gdt_flush]

;; _init_gdt:
;;	as	0x00 - first byte remains NULL 
;;	1	asx08 - kernel code segment - 0x00000000 to 0xFFFFFFFF - RW - PL0
;;	2	asx10 - kernel data segment - 0x00000000 to 0xFFFFFFFF - RW - PL0

_gdt_flush:

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
		ret						;now we have set cs to 0x08
