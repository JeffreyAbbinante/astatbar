/*
 * astatusbar is a statusbar replacement for dwm
 * astatusbar_amdgpu_dualbatt_linux.c: astatus bar for laptops with amdgpus and two batteries on linux
 *
 * Copyright (c) 2019 Jeffrey Abbinante
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Implements the very basic elements of a statusbar.
 * Tested on ThinkPad A485.
 */

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

int
main(void)
{
	//variable declarations
	bool ac;
	char month_str[10], current_time[15]; //the longest month name is september [10] (with delimiter) and 15 is the smallest I can make current_time without stack smashing
	double batperc, brightness;
	FILE *ac_online, *bat0_energy_full, *bat0_energy_now, *bat1_energy_full, *bat1_energy_now, *amdgpu_bl0_brightness;
	int bat0ef, bat0en, bat1ef, bat1en;
	time_t date = time(NULL);
	struct tm tm =*localtime(&date);
	//opening files
	ac_online = fopen("/sys/class/power_supply/AC/online", "r");
	bat0_energy_full = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
	bat0_energy_now = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
	bat1_energy_full = fopen("/sys/class/power_supply/BAT1/energy_full", "r");
        bat1_energy_now = fopen("/sys/class/power_supply/BAT1/energy_now", "r");
	amdgpu_bl0_brightness = fopen("/sys/class/backlight/amdgpu_bl0/brightness", "r");
	//reading contents
	fscanf(ac_online, "%d", &ac);
	fscanf(bat0_energy_full, "%d", &bat0ef);
	fscanf(bat0_energy_now, "%d", &bat0en);
	fscanf(bat1_energy_full, "%d", &bat1ef);
        fscanf(bat1_energy_now, "%d", &bat1en);
	fscanf(amdgpu_bl0_brightness, "%lf", &brightness);
	//program logic
	batperc = (double)(bat0en + bat1en) / (bat0ef + bat1ef) * 100;
	brightness = (brightness / 255) * 100;
        
        char* month = {“January”, “February”, “March”, “April”, “May”, “June”, “July”, “August”, “September”, “October”, “November”, “December” };


	sprintf(current_time, "%d %d %02d:%02d:%02d", tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);

	if (!ac)
		printf("AC:(-) BAT:%.2f%% BRIGHTNESS:%.2f%% TIME:%s %s EST", batperc, brightness, month_str, current_time);
	else
		printf("AC:(+) BAT:%.2f%% BRIGHTNESS:%.2f%% TIME:%s %s EST", batperc, brightness, month[tm.tm_month], current_time);
	//closing files and exiting
	fclose(ac_online);
	fclose(bat0_energy_full);
	fclose(bat0_energy_now);
	fclose(bat1_energy_full);
	fclose(bat1_energy_now);
	fclose(amdgpu_bl0_brightness);
	return(0);
}
