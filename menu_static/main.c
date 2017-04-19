#include "menu.h"
#include <stddef.h>
#include <stdio.h>
void sub_menu_maker(void* m);
int main()
{
	Menu m,subMenu1;
	subMenu1.entries[0].name="binary";
	subMenu1.entries[0].action=textFunc;
	subMenu1.entries[0].actionData="some text 2";
	subMenu1.entries[1].name="decimal";
	subMenu1.entries[1].action=textFunc;
	subMenu1.entries[1].actionData="some text 3";
	setNULL(2,&m);
	m.entries[0].name="Max out of n numbers";
	m.entries[0].action=textFunc;
	m.entries[0].actionData="some text 1";
	m.entries[1].name="Number of digits";
	m.entries[1].action=sub_menu_maker;
	m.entries[1].actionData=&subMenu1;
	m.entries[2].name="awhatever";
	m.entries[2].action=textFunc;
	m.entries[2].actionData="some  text 4 \n";
	setNULL(3,&m);
	executeMenu(&m);
	return 0;
	
}
void sub_menu_maker(void* m)
{
	executeMenu(m);
}
