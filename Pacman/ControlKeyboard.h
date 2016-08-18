#pragma once
/* Класс управления клавиатурой
 * 
 * 
 *
 */

#include "ControlManager.h"


class ControlKeyboard :	public ControlManager
{
public:
	ControlKeyboard(void);
	events get_event();
};

