#pragma once
/*  ласс управлени€
 * 
 * ≈диный класс дл€ получени€ направлени€ движение от клавиатуры и кинекта
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

