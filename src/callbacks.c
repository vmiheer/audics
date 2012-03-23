/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * callbacks.c
 * Copyright (C) miheer 2011 <v.miheer@gmail.com>
 * 
 * piano is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * piano is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include"testn.h"
#include "callbacks.h"
#include <pthread.h>
#include<assert.h>
int c1;
int c2;
struct par{
	int range;
	int freq;
};
int range;
int thrid;
#define MAX_THR 5
pthread_t tr[MAX_THR];
typedef struct par par;
par p;
extern gboolean
play_sa( GtkWidget   *widget)
{
	printf("hello");
	return 0;
}
void *tcompose_n_play(void* p)
{
		assert(((par*)p)->range <= 128);
		assert(((par*)p)->freq<=7);
		compose_and_play(((par*)p)->range,((par*)p)->freq);
		compose_and_play(((par*)p)->range,((par*)p)->freq);	
		pthread_exit(NULL);
}
extern gboolean
kb_press(GtkWidget *w, GdkEventKey *kevent, gpointer data)
{
	static par p;
	static thrid;
	printf("key pressed:%c\n",kevent->keyval);
//	printf("%d\n",kevent->keyval-'1');
	static int range;
	int freq;
	if(kevent->keyval=='q'||kevent->keyval=='w'||kevent->keyval=='e'||kevent->keyval=='r'||kevent->keyval=='t'||kevent->keyval=='y'||kevent->keyval=='u'||kevent->keyval=='i') 
	{
		switch(kevent->keyval) 
		{
			case 'q': range = 1;
					break;
			case 'w': range = 2;
					break;
			case 'e': range = 4;
					break;
			case 'r': range = 8;
					break;
			case 't': range = 16;
					break;
			case 'y': range = 32;
					break;
			case 'u': range = 64;
					break;
			case 'i': range = 128;
		}
	}
	else if (kevent->keyval=='1'||kevent->keyval=='2'||kevent->keyval=='3'||kevent->keyval=='4'||kevent->keyval=='5'||kevent->keyval=='6'||kevent->keyval=='7') 
	{
		pthread_t thr;
		p.range=range;
		printf("%s\n",gtk_button_get_label((GtkButton *)g_list_nth_data(gtk_container_get_children((GtkContainer*)w),(kevent->keyval)-'1')));
		freq = ((int)(kevent->keyval-'1'));
		printf("freq:%d",freq);
		p.freq=freq;
		assert(p.freq<=6);
		assert(p.range<=128);
		int rc = pthread_create(&tr[(thrid++)%MAX_THR], NULL, tcompose_n_play, (void *)&p);
		if(rc<0)
			fprintf(stderr,"Thread creation error\n");
		
		g_signal_emit_by_name((G_OBJECT((GtkButton *)g_list_nth_data(gtk_container_get_children((GtkContainer*)w),(kevent->keyval)-'1'))), "activate",NULL );
		c1=1;
	}
	return 0;
}
extern gboolean
say_hello(GtkWidget *w,gpointer data)
{
	printf("hello\n");
	printf("%s\n",gtk_button_get_label((GtkButton *)w));
/*	if ((char *)data=='1'||(char *)data=='2'||(char *)data=='3'||(char *)data=='4'||(char *)data=='5'||(char *)data=='6'||(char *)data=='7') 
	{
		g_signal_emit_by_name((G_OBJECT((GtkButton *)g_list_nth_data(gtk_container_get_children((GtkContainer*)w),(kevent->keyval)-'1'))), "activate",NULL );
		printf("%s\n",gtk_button_get_label((GtkButton *)g_list_nth_data(gtk_container_get_children((GtkContainer*)w),(kevent->keyval)-'1')));
		freq = ((int)(kevent->keyval-'1'));
		compose_and_play(range,freq);
		compose_and_play(range,freq);
		g_signal_emit_by_name((G_OBJECT((GtkButton *)g_list_nth_data(gtk_container_get_children((GtkContainer*)w),(kevent->keyval)-'1'))), "activate",NULL );
		c1=1;
	}	*/
	return 1;
}
void
destroy (GtkWidget *widget, gpointer data)
{
	gtk_main_quit ();
}
