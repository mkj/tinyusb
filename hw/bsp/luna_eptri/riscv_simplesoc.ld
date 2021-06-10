OUTPUT_FORMAT("elf32-littleriscv")
OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
    ram : ORIGIN = 0x00040000, LENGTH = 0x00010000
}

SECTIONS
{
	. = ORIGIN(ram);

	/* Start of day code. */
	.init :
	{
		*(.init) *(.init.*)
	} > ram
	.text :
	{
		*(.text) *(.text.*)
	} > ram

	.rodata :
	{
		*(.rodata) *(.rodata.*)
	} > ram
	.sdata :
	{
		PROVIDE(__global_pointer$ = .);
		*(.sdata) *(.sdata.*)
	} > ram
	.data :
	{
		*(.data) *(.data.*)
	} > ram
	.bss :
	{
		*(.bss) *(.bss.*)
	} > ram

}

PROVIDE(__stack_top = ORIGIN(ram) + LENGTH(ram));
