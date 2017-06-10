#ifndef __VIEW_COMMON_H__
#define __VIEW_COMMON_H__
#include <stdio.h>

typedef unsigned int  	u32_t;
typedef signed int 		s32_t;
typedef char 			str_t;

#define LOG_E(msg,...) fprintf(stderr,"%s:[E] " msg "\n", __FUNCTION__,##__VA_ARGS__)
#define LOG_W(msg,...) fprintf(stderr,"%s:[W] " msg "\n", __FUNCTION__,##__VA_ARGS__)
#define LOG_D(msg,...) fprintf(stderr,"%s:[D] " msg "\n", __FUNCTION__,##__VA_ARGS__)
#define LOG_I(msg,...) fprintf(stdout, msg "\n",##__VA_ARGS__)

typedef enum {
	VIEW_EVENT_BTN_HOME=100,
	VIEW_EVENT_BTN_BACK=200,
	VIEW_EVENT_BTN_NEXT=300,
	VIEW_EVENT_BTN_TERM=400,
	VIEW_EVENT_NONE=999
} view_event_t;

typedef enum {
	PANEL_ID_FRONT_001,
	PANEL_ID_FRONT_002,
	PANEL_ID_FRONT_003,
	PANEL_ID_FRONT_MAX
} panel_id_front_t;

typedef enum {
	PANEL_ID_BACK_001,
	PANEL_ID_BACK_002,
	PANEL_ID_BACK_MAX
} panel_id_back_t;



#endif
