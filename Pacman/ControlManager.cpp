#include "ControlManager.h"


ControlManager::ControlManager(void)
{
	cur_event = UP;
}

events ControlManager::get_event()
{
	
	return cur_event;
}
