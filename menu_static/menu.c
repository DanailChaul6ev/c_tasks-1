#include "menu.h"
#include <stdio.h>
#include <stddef.h>
#define clear() printf("\033[H\033[J")
void executeMenu(const Menu* m)
{
	clear();
	while (1)
	{
		for (int i=0;i<10;++i)
		{
			if(m->entries[i].name!=NULL)
			{
				printf("%d\t%s\n",i+1,m->entries[i].name);
			}
		}
		printf("0 Exit\n");
		int ent;
		printf("Choose entry:");
		scanf("%d",&ent);
		if (ent==0)
		{
			clear();
			return;
		}
		clear();
		m->entries[ent-1].action(m->entries[ent-1].actionData);
		printf("\n \n \n");
		
	}
}

void setNULL(int start,Menu* m)
{
	for (int i=start;i<100;i++)
	{
		m->entries[i].name=NULL;
	}
}
MenuEntry createPrintEntry(const char* name, const char* text)
{
	MenuEntry printEntry;
	printEntry.action=textFunc;
	printEntry.actionData=text;
	return printEntry;
}
MenuEntry createSubMenuEntry(const char* name,const Menu* subMenu)
{
	MenuEntry subEntry;
	subEntry.action = executeMenu;
	actionData = subMenu;
	return subMenu;
}
void fillSubMenuEntry(MenuEntry* outEntry, const char* name, const Menu* subMenu)
{
	outEntry->name = name;
	outEntry->actionData = subMenu;
	outEntry->action = executeMenu;
}
void fillPrintEntry(MenuEntry* outEntry, const char* name, const char* text)
{
	outEntry->name = name;
	outEntry->acton=textFunc;
	outEntry->actionData=text;
}
void textFunc(void* b)
{
	printf("%s \n",b);
}
