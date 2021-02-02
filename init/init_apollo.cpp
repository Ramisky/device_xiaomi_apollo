/*
   Copyright (c) 2020, The LineageOS Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fstream>

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "vendor_init.h"
#include "property_service.h"

using android::base::GetProperty;

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void vendor_load_properties() {
    std::string region = GetProperty("ro.boot.hwc", "");
    std::string product = GetProperty("ro.boot.product.hardware.sku", "");

    property_override("ro.oem_unlock_supported", "0");
    property_override("ro.build.description", "redfin-user 11 RQ2A.210305.006 7119741 release-keys");
    property_override("ro.build.fingerprint", "google/redfin/redfin:11/RQ2A.210305.006/7119741:user/release-keys");
    if (product.find("std") != std::string::npos) {
        if (region.find("GLOBAL") != std::string::npos) {
            property_override("ro.product.brand", "Xiaomi");
            property_override("ro.product.model", "Mi 10T");
            property_override("ro.product.device", "apollo");
        } else if (region.find("CN") != std::string::npos) {
            property_override("ro.product.brand", "Redmi");
            property_override("ro.product.model", "Redmi K30s Ultra");
            property_override("ro.product.device", "apollo");
        }
    } else if (product.find("pro") != std::string::npos) {
        if (region.find("GLOBAL") != std::string::npos) {
            property_override("ro.product.brand", "Xiaomi");
            property_override("ro.product.model", "Mi 10T Pro");
            property_override("ro.product.device", "apollopro");
        } else if (region.find("INDIA") != std::string::npos) {
            property_override("ro.product.brand", "Xiaomi");
            property_override("ro.product.model", "Mi 10T Pro");
            property_override("ro.product.device", "apollopro");
        }
    }
}
