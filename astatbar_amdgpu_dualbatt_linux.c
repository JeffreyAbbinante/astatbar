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
	char month_str[9], current_time[15]; //the longest month name is september [9] and 15 is the smallest I can make current_time without stack smashing
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
	switch (tm.tm_mon) {
	case 0:
		sprintf(month_str, "January");
		break;
	case 1:
		sprintf(month_str, "Febuary");
		break;
	case 2:
		sprintf(month_str, "March");
		break;
	case 3:
		sprintf(month_str, "April");
		break;
	case 4:
		sprintf(month_str, "May");
		break;
	case 5:
		sprintf(month_str, "June");
		break;
	case 6:
		sprintf(month_str, "July");
		break;
	case 7:
		sprintf(month_str, "August");
		break;
	case 8:
		sprintf(month_str, "September");
		break;
	case 9:
		sprintf(month_str, "October");
		break;
	case 10:
		sprintf(month_str, "November");
		break;
	case 11:
		sprintf(month_str, "December");
		break;
	default:
		break;
	}
	sprintf(current_time, "%d %d %02d:%02d:%02d", tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	if (!ac)
		printf("AC:(-) BAT:%.2f%% BRIGHTNESS:%.2f%% TIME:%s %s EST", batperc, brightness, month_str, current_time);
	else
		printf("AC:(+) BAT:%.2f%% BRIGHTNESS:%.2f%% TIME:%s %s EST", batperc, brightness, month_str, current_time);
	//closing files and exiting
	fclose(ac_online);
	fclose(bat0_energy_full);
	fclose(bat0_energy_now);
	fclose(bat1_energy_full);
	fclose(bat1_energy_now);
	fclose(amdgpu_bl0_brightness);
	return(0);
}
