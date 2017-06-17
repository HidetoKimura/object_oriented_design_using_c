#include <string.h>
#include <stdlib.h>
#include "view_common.h"

typedef struct {
	str_t*	name;
} pnl_mng_tbl_t;

typedef struct {
	s32_t	now_panel_id;
	s32_t	next_panel_id;
	s32_t   panel_num;
	pnl_mng_tbl_t** panels;
} view_mng_tbl_t;

view_mng_tbl_t g_view_mng;

static const str_t* front_panel_namelist[] = {
	"front_001", "front_002", "front_003"
};


void front_001_active(void)
{
	LOG_D("");
}

void front_001_inactive(void)
{
	LOG_D("");
}
void front_001_invoke(view_event_t event)
{
	s32_t next_panel_id;

	LOG_D("event = %d", event);
	switch(event) {
		case VIEW_EVENT_BTN_BACK:
			next_panel_id = PANEL_ID_FRONT_001;
			break;
 		case VIEW_EVENT_BTN_NEXT:
			next_panel_id = PANEL_ID_FRONT_002;
			break;
		case VIEW_EVENT_BTN_HOME:
  		default:
			next_panel_id = PANEL_ID_FRONT_001;
			break;
	}
	g_view_mng.next_panel_id = next_panel_id;
}


void front_002_active(void)
{
	LOG_D("");
}

void front_002_inactive(void)
{
	LOG_D("");
}

void front_002_invoke(view_event_t event)
{
	s32_t next_panel_id;

	LOG_D("event = %d", event);
	switch(event) {
		case VIEW_EVENT_BTN_BACK:
			next_panel_id = PANEL_ID_FRONT_001;
			break;
 		case VIEW_EVENT_BTN_NEXT:
			next_panel_id = PANEL_ID_FRONT_003;
			break;
		case VIEW_EVENT_BTN_HOME:
  		default:
			next_panel_id = PANEL_ID_FRONT_001;
			break;
	} 
	g_view_mng.next_panel_id = next_panel_id;
}

void front_003_active(void)
{
	LOG_D("");
}

void front_003_inactive(void)
{
	LOG_D("");
}

void front_003_invoke(view_event_t event)
{
	s32_t next_panel_id;

	LOG_D("event = %d", event);
	switch(event) {
		case VIEW_EVENT_BTN_BACK:
			next_panel_id = PANEL_ID_FRONT_002;
			break;
 		case VIEW_EVENT_BTN_NEXT:
			next_panel_id = PANEL_ID_FRONT_003;
			break;
		case VIEW_EVENT_BTN_HOME:
  		default:
			next_panel_id = PANEL_ID_FRONT_001;
			break;
	} 
	g_view_mng.next_panel_id = next_panel_id;
}


void view_init(void)
{
	s32_t i;
	
	LOG_D("");
	g_view_mng.now_panel_id = PANEL_ID_FRONT_001;
	g_view_mng.next_panel_id = PANEL_ID_FRONT_001;
	
	g_view_mng.panel_num = PANEL_ID_FRONT_MAX;
	g_view_mng.panels = malloc(sizeof(pnl_mng_tbl_t*) * PANEL_ID_FRONT_MAX);
	
	for(i = 0; i < g_view_mng.panel_num; i++) {	
		g_view_mng.panels[i] = malloc(sizeof(pnl_mng_tbl_t));
		g_view_mng.panels[i]->name = (str_t*)front_panel_namelist[i];
	}
}
 
void view_deinit(void)
{
	s32_t i;
	
	LOG_D("");
	for(i = 0; i < g_view_mng.panel_num; i++) {	
		free(g_view_mng.panels[i]);
	}

	free(g_view_mng.panels); 
	g_view_mng.panel_num = 0;

	g_view_mng.now_panel_id = 0;
	g_view_mng.next_panel_id = 0;
	
}

void event_invoke(view_event_t event)
{

	LOG_D("event = %d", event);

	/* deterime next panel id  */
	switch(g_view_mng.now_panel_id) {
		case PANEL_ID_FRONT_001:
			front_001_invoke(event);
			break;
		case PANEL_ID_FRONT_002:
			front_002_invoke(event);
			break;
		case PANEL_ID_FRONT_003:
			front_003_invoke(event);
			break;
	}
	LOG_D("now_penel = %s, next_panel = %s", 
		g_view_mng.panels[g_view_mng.now_panel_id]->name,
		g_view_mng.panels[g_view_mng.next_panel_id]->name);

	/* If there is no change panel id, then do no operation. */
	if(g_view_mng.now_panel_id == g_view_mng.next_panel_id) return;

	/* inactive view */
	switch(g_view_mng.now_panel_id) {
		case PANEL_ID_FRONT_001:
			front_001_inactive();
			break;
		case PANEL_ID_FRONT_002:
			front_002_inactive();
			break;
		case PANEL_ID_FRONT_003:
			front_003_inactive();
			break;
	}

	/* active view */
	switch(g_view_mng.next_panel_id) {
		case PANEL_ID_FRONT_001:
			front_001_active();
			break;
		case PANEL_ID_FRONT_002:
			front_002_active();
			break;
		case PANEL_ID_FRONT_003:
			front_003_active();
			break;
	}
	g_view_mng.now_panel_id = g_view_mng.next_panel_id;

	return;
}


