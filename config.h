/*
 * config.h: configuration file for astatbar.c
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
 */

#ifndef ASTATBAR_CONFIG_H
#define ASTATBAR_CONFIG_H

//modify this to set the output of the timezone_str string, "UTC" otherwise
const char timezone_str[] = "UTC";

//uncomment this to set astatbar in openbsd mode, linux mode otherwise
//#define OPENBSD

//uncomment this to set astatbar in laptop mode, desktop mode otherwise
//#define LAPTOP

//uncomment this to set astatbar in dual battery mode, single battery mode otherwise (depends on laptop mode being enabled)
//#define DUAL_BAT

//uncomment this to set astatbar in amdgpu mode, intelgpu mode otherwise (depends on laptop mode being enabled)
//#define AMDGPU

#endif
