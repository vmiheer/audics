/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */
#ifndef __TESTN_H__
#define __TESTN_H__
#define ALSA_PCM_NEW_HW_PARAMS_API
#include<stdio.h>
#include <alsa/asoundlib.h>
#include<math.h>
#include<ncurses.h>
#include<malloc.h>
#include<alloca.h>
#include<assert.h>
#include<unistd.h>

void compose_and_play(int inc_factor,int buff_id);
static short *buffer_array[7];
static short buff8[512];
static short *writer;
static int cnt=-1;
static snd_pcm_t *handlec;
void damp(int);
void fill();
void init_alsa();
#endif 