/*
 * Copyright (C) 2017 YU Community OS Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "log.h"
#include "property_service.h"
#include "util.h"
#include "vendor_init.h"

#define DRV_INFO "/sys/devices/platform/fp_drv/fp_drv_info"

static void fp_prop()
{
    int fd = open(DRV_INFO, 0);
    if (fd <= 0) {
        ERROR("Cannot open: %s", DRV_INFO);
    }

    char fp_drv[50];
    memset(fp_drv, 0, sizeof(fp_drv));
    int result = read(fd, fp_drv, sizeof(fp_drv));

    if (strcmp(fp_drv, "elan_fp") == 0) {
        property_set("persist.sys.fp.goodix", "0");
    } else if (strcmp(fp_drv, "goodix_fp") == 0) {
        property_set("persist.sys.fp.goodix", "1");
    } else if (strcmp(fp_drv, "silead_fp_dev") == 0) {
        ERROR("%s: Silead fpsvcd fingerprint sensor is unsupported", __func__);
    } else {
        ERROR("%s: Fingerprint sensor is unsupported", __func__);
    }
    close(fd);
}

void vendor_load_properties()
{
    fp_prop();

    property_set("dalvik.vm.heapstartsize", "16m");
    property_set("dalvik.vm.heapgrowthlimit", "256m");
    property_set("dalvik.vm.heapsize", "512m");
    property_set("dalvik.vm.heaptargetutilization", "0.75");
    property_set("dalvik.vm.heapminfree", "4m");
    property_set("dalvik.vm.heapmaxfree", "8m");

    property_set("ro.hwui.texture_cache_size", "72");
    property_set("ro.hwui.layer_cache_size", "48");
    property_set("ro.hwui.r_buffer_cache_size", "8");
    property_set("ro.hwui.path_cache_size", "32");
    property_set("ro.hwui.gradient_cache_size", "1");
    property_set("ro.hwui.drop_shadow_cache_size", "6");
    property_set("ro.hwui.texture_cache_flushrate", "0.4");
    property_set("ro.hwui.text_small_cache_width", "1024");
    property_set("ro.hwui.text_small_cache_height", "1024");
    property_set("ro.hwui.text_large_cache_width", "2048");
    property_set("ro.hwui.text_large_cache_height", "2048");

}

