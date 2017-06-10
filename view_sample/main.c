#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "view_common.h"
#include "view_class.h"
#include "view_carnavi.h"

#define MYSIG_HOME	(SIGRTMIN+1)
#define MYSIG_BACK	(SIGRTMIN+2)
#define MYSIG_NEXT	(SIGRTMIN+3)
#define MYSIG_TERM	(SIGRTMIN+4)

static view_event_t	g_event = VIEW_EVENT_NONE;

static void event_handler(int signo)
{
	if(signo == MYSIG_HOME) {
		g_event = VIEW_EVENT_BTN_HOME;
	} else if(signo == MYSIG_BACK) {
		g_event = VIEW_EVENT_BTN_BACK;
	} else if(signo == MYSIG_NEXT) {
		g_event = VIEW_EVENT_BTN_NEXT;
	} else if(signo == MYSIG_TERM) {
		g_event = VIEW_EVENT_BTN_TERM;
	}
	return;
}

static void sig_init(void)
{
    int ret;

    struct sigaction act;
    sigset_t sigset;

    ret = sigemptyset(&sigset);
    if (ret < 0) {
        LOG_E("sigemptyset err = %s", strerror(errno));
        return;
    }

    memset(&act, 0, sizeof(act));
    act.sa_handler = event_handler;
    act.sa_mask = sigset;

    ret = sigaction(MYSIG_HOME, &act, NULL);
    if (ret < 0) {
        LOG_E("sigaction err = %s",  strerror(errno));
        return ;
    }

    ret = sigaction(MYSIG_BACK, &act, NULL);
    if (ret < 0) {
        LOG_E("sigaction err = %s",  strerror(errno));
        return ;
    }
    
	ret = sigaction(MYSIG_NEXT, &act, NULL);
    if (ret < 0) {
        LOG_E("sigaction err = %s",  strerror(errno));
        return ;
    }
    
	ret = sigaction(MYSIG_TERM, &act, NULL);
    if (ret < 0) {
        LOG_E("sigaction err = %s",  strerror(errno));
        return ;
    }
    
	return;
}

int main(void) 
{
	int ret;

	LOG_I("<<USAGE>>");
	LOG_I("HOME:\nkillall view_sample -%d", MYSIG_HOME);
	LOG_I("BACK:\nkillall view_sample -%d", MYSIG_BACK);
	LOG_I("NEXT:\nkillall view_sample -%d", MYSIG_NEXT);
	LOG_I("TERM:\nkillall view_sample -%d", MYSIG_TERM);

	sig_init();
	view_init();

	/* for initial screen */
	event_invoke(VIEW_EVENT_BTN_HOME);

	while(1) {
		ret = select(0, NULL, NULL, NULL, NULL);
		if( ret < 0 && errno == EINTR) {
			LOG_I("recv event = %d", g_event);
			if(g_event == VIEW_EVENT_BTN_TERM) {
				break;
			}
			event_invoke(g_event);
			g_event = VIEW_EVENT_NONE;
		}
	}	
	view_deinit();

	return 0;
}

