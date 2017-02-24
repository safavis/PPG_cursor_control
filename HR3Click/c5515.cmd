/*-c
/*-stack 0x7000                   /* PRIMARY STACK SIZE               */
/*-sstack 0x2000                /* SECONDARY STACK SIZE             */
/*-heap  0x1000                   /* HEAP AREA SIZE  */


/* Set entry point to Reset vector                                  */
/* - Allows Reset ISR to force IVPD/IVPH to point to vector table.  */
/*-e reset_isr */

MEMORY
{
    MMR		(RW)	: origin = 0000000h length = 0000c0h	/* MMRs */
    VEC     (RX)	: origin = 00000C0h length = 000300h	/* on-chip ROM vectors */

    DARAM	(RW)    : origin = 00003C0h length = 00fc40h	/* on-chip DARAM */
    SARAM	(RW)	: origin = 0010000h length = 040000h	/* on-chip SARAM */

    SAROM_0 (RX)	: origin = 0fe0000h length = 008000h 	/* on-chip ROM 0 */
    SAROM_1 (RX)	: origin = 0fe8000h length = 008000h 	/* on-chip ROM 1 */
    SAROM_2 (RX)	: origin = 0ff0000h length = 008000h 	/* on-chip ROM 2 */
    SAROM_3 (RX)	: origin = 0ff8000h length = 008000h 	/* on-chip ROM 3 */

    EMIF_CS0 (RW)	: origin = 0050000h	length = 07B0000h   /* mSDR */
	EMIF_CS2 (RW)	: origin = 0800000h	length = 0400000h   /* ASYNC1 : NAND */
	EMIF_CS3 (RW)	: origin = 0C00000h	length = 0200000h   /* ASYNC2 : NOR  */
	EMIF_CS4 (RW)	: origin = 0E00000h	length = 0100000h   /* ASYNC3 : SRAM */
	EMIF_CS5 (RW)	: origin = 0F00000h	length = 00E0000h   /* ASYNC4 : SRAM */

}

SECTIONS
{
	vectors (NOLOAD)
    vector      : > VEC		ALIGN = 256
    .text       : > SARAM	//ALIGN = 4
    .stack      : > SARAM	//ALIGN = 2
    .sysstack   : > SARAM	//ALIGN = 2

	.switch		: > SARAM
    .data       : > DARAM
    .bss        : > DARAM//, fill = 0
	.cinit 		: > SARAM
	.const 		: > SARAM
	.cio		: > SARAM
	.sysmem 	: > SARAM
//	.WorkBuffer : > SARAM
//	.Coeff		: > SARAM
	.usect   	: > DARAM
//	.buffer1   	: > DARAM
//	.buffer2   	: > DARAM

	.emif_cs0   : > EMIF_CS0
	.emif_cs2   : > EMIF_CS2
	.emif_cs3   : > EMIF_CS3
	.emif_cs4   : > EMIF_CS4
	.emif_cs5   : > EMIF_CS5


}
