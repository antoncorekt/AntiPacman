#pragma once
/* ����� ����������
 * 
 * ������ ����� ��� ��������� ����������� �������� �� ���������� � �������
 *
 */

#include "constant.h"


class ControlManager
{
	events cur_event;

public:
	ControlManager(void);
	
	virtual events get_event() ;
};

