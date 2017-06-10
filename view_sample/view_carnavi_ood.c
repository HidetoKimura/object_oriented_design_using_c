#include <string.h>
#include <stdlib.h>
#include "view_common.h"
#include "view_class.h"

static view_obj_t *front_view1;
static view_obj_t *back_view1;


static s32_t front_001_event(panel_obj_t* obj, view_event_t event)
{
    LOG_D("%s, event = %d", obj->name, event);

	switch(event) {
		case VIEW_EVENT_BTN_BACK:
			return PANEL_ID_FRONT_001;
 		case VIEW_EVENT_BTN_NEXT:
			return PANEL_ID_FRONT_002;
		case VIEW_EVENT_BTN_HOME:
  		default:
			return PANEL_ID_FRONT_001;
	} 
}

static s32_t front_002_event(panel_obj_t* obj, view_event_t event)
{
    LOG_D("%s, event = %d", obj->name, event);

	switch(event) {
		case VIEW_EVENT_BTN_BACK:
			return PANEL_ID_FRONT_001;
 		case VIEW_EVENT_BTN_NEXT:
			return PANEL_ID_FRONT_003;
		case VIEW_EVENT_BTN_HOME:
  		default:
			return PANEL_ID_FRONT_001;
	} 
}

static s32_t front_003_event(panel_obj_t* obj, view_event_t event)
{
    LOG_D("%s, event = %d", obj->name, event);

	switch(event) {
		case VIEW_EVENT_BTN_BACK:
			return PANEL_ID_FRONT_002;
 		case VIEW_EVENT_BTN_NEXT:
			return PANEL_ID_FRONT_003;
		case VIEW_EVENT_BTN_HOME:
  		default:
			return PANEL_ID_FRONT_001;
	} 
}

static s32_t back_001_event(panel_obj_t* obj, view_event_t event)
{
    LOG_D("%s, event = %d", obj->name, event);

	switch(event) {
		case VIEW_EVENT_BTN_BACK:
			return PANEL_ID_BACK_001;
 		case VIEW_EVENT_BTN_NEXT:
			return PANEL_ID_BACK_002;
		case VIEW_EVENT_BTN_HOME:
  		default:
			return PANEL_ID_BACK_001;
	} 
}

static s32_t back_002_event(panel_obj_t* obj, view_event_t event)
{
    LOG_D("%s, event = %d", obj->name, event);

	switch(event) {
		case VIEW_EVENT_BTN_BACK:
			return PANEL_ID_BACK_001;
 		case VIEW_EVENT_BTN_NEXT:
			return PANEL_ID_BACK_002;
		case VIEW_EVENT_BTN_HOME:
  		default:
			return PANEL_ID_BACK_001;
	} 
}

static const str_t* front_panel_namelist[] = {
	"front_001", "front_002", "front_003"
};

static const str_t* back_panel_namelist[] = {
	"back_001", "back_002" 
};

static panel_ops_t front_panel_opslist[] = {
	[PANEL_ID_FRONT_001] = {
		.callback_event = front_001_event,
	},
	[PANEL_ID_FRONT_002] = {
		.callback_event = front_002_event,
	},
	[PANEL_ID_FRONT_003] = {
		.callback_event = front_003_event,
	}
};
	
static panel_ops_t back_panel_opslist[] = {
	[PANEL_ID_BACK_001] = {
		.callback_event = back_001_event,
	},
	[PANEL_ID_BACK_002] = {
		.callback_event = back_002_event,
	},
};

static void front_view_constructor(view_obj_t* view_obj, void *ext)
{
	s32_t i;
	panel_obj_t *tmp_panel;

    LOG_D("%s", view_obj->name);

	view_obj->now_panel_id = PANEL_ID_FRONT_001;
	view_obj->next_panel_id = PANEL_ID_FRONT_001;
	view_obj->panel_num = PANEL_ID_FRONT_MAX;
	view_obj->panels = malloc(sizeof(panel_obj_t*) * PANEL_ID_FRONT_MAX);

	for(i = 0; i < view_obj->panel_num; i++) {
		panel_create(&tmp_panel, (str_t*)front_panel_namelist[i], &front_panel_opslist[i]); 
		view_obj->panels[i] = tmp_panel;
	}	

}

static void back_view_constructor(view_obj_t* view_obj, void *ext)
{
	s32_t i;
	panel_obj_t *tmp_panel;

    LOG_D("%s", view_obj->name);

	view_obj->now_panel_id = PANEL_ID_BACK_001;
	view_obj->next_panel_id = PANEL_ID_BACK_001;
	view_obj->panel_num = PANEL_ID_BACK_MAX;
	view_obj->panels = malloc(sizeof(panel_obj_t*) * PANEL_ID_BACK_MAX);

	for(i = 0; i < view_obj->panel_num; i++) {
		panel_create(&tmp_panel, (str_t*)back_panel_namelist[i], &back_panel_opslist[i]); 
		view_obj->panels[i] = tmp_panel;
	}	

}
void view_init(void)
{
	view_ops_t ops;

	memset(&ops, 0x00, sizeof(ops));	
	ops.constructor = front_view_constructor;

	view_create(&front_view1, "front_view1", &ops); 

	memset(&ops, 0x00, sizeof(ops));	
	ops.constructor = back_view_constructor;

	view_create(&back_view1, "back_view1", &ops); 
}
 
void view_deinit(void)
{
	view_destroy(front_view1); 
	view_destroy(back_view1); 
}

void event_invoke(view_event_t event)
{

	front_view1->ops.invoke(front_view1, event);
	back_view1->ops.invoke(back_view1, event);
	return;
}


