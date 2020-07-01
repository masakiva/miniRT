#include "errors.h"

void	print_elem_err_msg5(uint8_t type_index)
{
	if (type_index == 8)
	{
		putstr_stderr(E_LIG1);
		putstr_stderr(E_LIG2);
		putstr_stderr(E_LIG3);
		putstr_stderr(E_LIG4);
		putstr_stderr(E_LIG5);
		putstr_stderr(E_LIG6);
	}
	else if (type_index == 9)
	{
		putstr_stderr(E_ID1);
		putstr_stderr(E_ID2);
	}
}

void	print_elem_err_msg4(uint8_t type_index)
{
	if (type_index == 6)
	{
		putstr_stderr(E_CYL1);
		putstr_stderr(E_CYL2);
		putstr_stderr(E_CYL3);
		putstr_stderr(E_CYL4);
		putstr_stderr(E_CYL5);
		putstr_stderr(E_CYL6);
		putstr_stderr(E_CYL7);
		putstr_stderr(E_CYL8);
		putstr_stderr(E_CYL9);
		putstr_stderr(E_CYL10);
	}
	else if (type_index == 7)
	{
		putstr_stderr(E_CAM1);
		putstr_stderr(E_CAM2);
		putstr_stderr(E_CAM3);
		putstr_stderr(E_CAM4);
		putstr_stderr(E_CAM5);
		putstr_stderr(E_CAM6);
		putstr_stderr(E_CAM7);
		putstr_stderr(E_CAM8);
	}
}

void	print_elem_err_msg3(uint8_t type_index)
{
	if (type_index == 4)
	{
		putstr_stderr(E_TRI1);
		putstr_stderr(E_TRI2);
		putstr_stderr(E_TRI3);
		putstr_stderr(E_TRI4);
		putstr_stderr(E_TRI5);
		putstr_stderr(E_TRI6);
		putstr_stderr(E_TRI7);
		putstr_stderr(E_TRI8);
	}
	else if (type_index == 5)
	{
		putstr_stderr(E_SQU1);
		putstr_stderr(E_SQU2);
		putstr_stderr(E_SQU3);
		putstr_stderr(E_SQU4);
		putstr_stderr(E_SQU5);
		putstr_stderr(E_SQU6);
		putstr_stderr(E_SQU7);
		putstr_stderr(E_SQU8);
		putstr_stderr(E_SQU9);
	}
}

void	print_elem_err_msg2(uint8_t type_index)
{
	if (type_index == 2)
	{
		putstr_stderr(E_SPH1);
		putstr_stderr(E_SPH2);
		putstr_stderr(E_SPH3);
		putstr_stderr(E_SPH4);
		putstr_stderr(E_SPH5);
		putstr_stderr(E_SPH6);
	}
	else if (type_index == 3)
	{
		putstr_stderr(E_PLA1);
		putstr_stderr(E_PLA2);
		putstr_stderr(E_PLA3);
		putstr_stderr(E_PLA4);
		putstr_stderr(E_PLA5);
		putstr_stderr(E_PLA6);
		putstr_stderr(E_PLA7);
		putstr_stderr(E_PLA8);
	}
}

void	print_elem_err_msg1(uint8_t type_index)
{
	if (type_index == 0)
	{
		putstr_stderr(E_RES1);
		putstr_stderr(E_RES2);
		putstr_stderr(E_RES3);
		putstr_stderr(E_RES4);
		putstr_stderr(E_RES5);
		putstr_stderr(E_RES6);
	}
	else if (type_index == 1)
	{
		putstr_stderr(E_AMB1);
		putstr_stderr(E_AMB2);
		putstr_stderr(E_AMB3);
		putstr_stderr(E_AMB4);
		putstr_stderr(E_AMB5);
		putstr_stderr(E_AMB6);
	}
}
