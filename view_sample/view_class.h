#ifndef __VIEW_CLASS_H__
#define __VIEW_CLASS_H__

#include "view_common.h"

typedef struct _view_obj_t view_obj_t;
typedef struct _panel_obj_t panel_obj_t;

typedef struct {
    void (*constructor)(view_obj_t*, void *);
    void (*invoke)(view_obj_t*, s32_t event);
    void (*destructor)(view_obj_t*, void *);
} view_ops_t;


struct _view_obj_t {
	str_t*	name;
	s32_t	now_panel_id;
	s32_t	next_panel_id;
	s32_t   panel_num;
	panel_obj_t** panels;
	view_ops_t ops;
};

typedef struct {
    void (*constructor)(panel_obj_t*, void *);
    void (*active_view)(panel_obj_t*, void *);
    void (*inactive_view)(panel_obj_t*, void *);
    s32_t (*callback_event)(panel_obj_t*, view_event_t event);
    void (*destructor)(panel_obj_t*, void *);
} panel_ops_t;

struct _panel_obj_t {
	str_t*	name;
	panel_ops_t ops;
};

void view_create(view_obj_t**, str_t* name, view_ops_t* ovr);
void view_destroy(view_obj_t*);

void panel_create(panel_obj_t**, str_t* name, panel_ops_t* ovr);
void panel_destroy(panel_obj_t*);
#endif
