/*
 * astatusbar is a statusbar replacement for dwm
 * astatusbar_intelgpu_singlbatt_linux.c: astatus bar for laptops with intel gpus and one battery on linux
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
 * Tested on ThinkPad X1C7.
 */

#include <stdio.h>
#include <time.h>

int
main(void)
{
	//variable declarations
	const char *month_str[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	double batperc, brightness;
	FILE *ac_online, *intel_backlight_brightness, *bat0_energy_full, *bat0_energy_now;
	int ac, bat0ef, bat0en;
	time_t date = time(NULL);
	struct tm tm =*localtime(&date);
	//opening files
	ac_online = fopen("/sys/class/power_supply/AC/online", "r");
	intel_backlight_brightness = fopen("/sys/class/backlight/intel_backlight/brightness", "r");
	bat0_energy_full = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
	bat0_energy_now = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
	//reading contents
	fscanf(ac_online, "%d", &ac);
	fscanf(intel_backlight_brightness, "%lf", &brightness);
	fscanf(bat0_energy_full, "%d", &bat0ef);
	fscanf(bat0_energy_now, "%d", &bat0en);
	//program logic
	batperc = (double)(bat0en) / (bat0ef) * 100;
	brightness = (brightness / 24242) * 100;
	if (ac == 0)
		printf("AC:(-) BAT:(-)%.2f%% BRIGHTNESS:%.2f%% TIME:%s %d, %d %02d:%02d:%02d EST", batperc, brightness, month_str[tm.tm_mon], tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	else if (ac == 1 && batperc > 98)
		printf("AC:(+) BAT:FULL BRIGHTNESS:%.2f%% TIME:%s %d, %d %02d:%02d:%02d EST", brightness, month_str[tm.tm_mon], tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	else
		printf("AC:(+) BAT:(+)%.2f%% BRIGHTNESS:%.2f%% TIME:%s %d, %d %02d:%02d:%02d EST", batperc, brightness, month_str[tm.tm_mon], tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	//closing files and exiting
	fclose(ac_online);
	fclose(intel_backlight_brightness);
	fclose(bat0_energy_full);
	fclose(bat0_energy_now);
	return(0);
}
