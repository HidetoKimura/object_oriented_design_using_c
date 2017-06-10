#include <string.h>
#include <stdlib.h>
#include "view_class.h"

static void view_base_constructor(view_obj_t* obj, void *ext)
{
	LOG_D("%s", obj->name);
}
static void view_base_invoke(view_obj_t* obj, s32_t event)
{
	panel_obj_t *now_panel, *next_panel;
	s32_t now_panel_id, next_panel_id;

	LOG_D("%s", obj->name);

	now_panel_id = obj->now_panel_id;
	now_panel = obj->panels[obj->now_panel_id];

    next_panel_id = now_panel->ops.callback_event(now_panel, event);
	next_panel = obj->panels[next_panel_id];

	LOG_D("now_panel = %s, next_panel = %s", now_panel->name, next_panel->name);

	if(now_panel_id != next_panel_id) {
		now_panel->ops.inactive_view(now_panel, NULL);
		next_panel->ops.active_view(next_panel, NULL);
	}

	obj->now_panel_id = next_panel_id;
}

static void view_base_destructor(view_obj_t* obj, void *ext)
{
	s32_t i;

    LOG_D("view_base_destructor - %s", obj->name);

	for(i = 0; i < obj->panel_num; i++) {
		obj->panels[i]->ops.destructor(obj->panels[i], NULL);
	}

	free(obj->panels);
	obj->panel_num = 0;

	obj->name = NULL;
	obj->now_panel_id = 0;
	obj->next_panel_id = 0;

	return;
} 
static void panel_base_constructor(panel_obj_t* obj, void *ext)
{
    LOG_D("%s", obj->name);
}
static void panel_base_active_view(panel_obj_t* obj, void *ext)
{
    LOG_D("%s", obj->name);
}
static void panel_base_inactive_view(panel_obj_t* obj, void *ext)
{
    LOG_D("%s", obj->name);
}
static s32_t panel_base_callback_event(panel_obj_t* obj, view_event_t event)
{
    LOG_D("%s", obj->name);
	return 0;
}
static void panel_base_destructor(panel_obj_t* obj, void *ext)
{
    LOG_D("%s", obj->name);
	
	obj->name = NULL;
}

void view_create(view_obj_t** obj, str_t* name, view_ops_t* ovr)
{
	view_obj_t* view_obj;

	LOG_D("%s", name);

	view_obj = malloc(sizeof(view_obj_t));
	if(view_obj == NULL) return;

	view_obj->name = name;
	view_obj->now_panel_id = 0;
	view_obj->next_panel_id = 0;
	view_obj->panel_num = 0;
	view_obj->panels = NULL;

	if(ovr->constructor) {
		view_obj->ops.constructor = ovr->constructor;
	}
	else {
		view_obj->ops.constructor = view_base_constructor;
	}
	if(ovr->destructor) {
		view_obj->ops.destructor = ovr->destructor;
	}
	else {
		view_obj->ops.destructor = view_base_destructor;
	}
	if(ovr->invoke) {
		view_obj->ops.invoke = ovr->invoke;
	}
	else {
		view_obj->ops.invoke = view_base_invoke;
	}
	
	view_obj->ops.constructor(view_obj, NULL);

	*obj = view_obj;
	return;
}
void view_destroy(view_obj_t* view_obj)
{
	LOG_D("%s", view_obj->name);
	view_obj->ops.destructor(view_obj, NULL);
	free(view_obj);
	return;
}
void panel_create(panel_obj_t** obj, str_t* name, panel_ops_t* ovr)
{
	panel_obj_t* panel_obj;

	LOG_D("%s", name);

	panel_obj = malloc(sizeof(panel_obj_t));
	if(panel_obj == NULL) return;

	panel_obj->name = name;

	if(ovr->constructor) {
		panel_obj->ops.constructor = ovr->constructor;
	}
	else {
		panel_obj->ops.constructor = panel_base_constructor;
	}
	if(ovr->destructor) {
		panel_obj->ops.destructor = ovr->destructor;
	}
	else {
		panel_obj->ops.destructor = panel_base_destructor;
	}
	if(ovr->active_view) {
		panel_obj->ops.active_view = ovr->active_view;
	}
	else {
		panel_obj->ops.active_view = panel_base_active_view;
	}
	if(ovr->inactive_view) {
		panel_obj->ops.inactive_view = ovr->inactive_view;
	}
	else {
		panel_obj->ops.inactive_view = panel_base_inactive_view;
	}
	if(ovr->callback_event) {
		panel_obj->ops.callback_event = ovr->callback_event;
	}
	else {
		panel_obj->ops.callback_event = panel_base_callback_event;
	}

	panel_obj->ops.constructor(panel_obj, NULL);

	*obj = panel_obj;
	return;
}
void panel_destroy(panel_obj_t* panel_obj)
{
	LOG_D("panel_destoroy - %s", panel_obj->name);
	panel_obj->ops.destructor(panel_obj, NULL);
	free(panel_obj);
	return;
}


