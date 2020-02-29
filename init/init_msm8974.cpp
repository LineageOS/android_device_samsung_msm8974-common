/*
   Copyright (c) 2016, The CyanogenMod Project. All rights reserved.
   Copyright (c) 2017-2020, The LineageOS Project. All rights reserved.

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

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"

#include "init_msm8974.h"

using android::init::property_set;

void set_rild_libpath(char const variant[])
{
    std::string libpath("/system/vendor/lib/libsec-ril.");
    libpath += variant;
    libpath += ".so";

    property_override("rild.libpath", libpath.c_str());
}

void cdma_properties(char const operator_alpha[],
        char const operator_numeric[],
        char const default_cdma_sub[],
        char const default_network[],
        char const rild_lib_variant[])
{
    // Dynamic CDMA Properties
    property_set("ro.cdma.home.operator.alpha", operator_alpha);
    property_set("ro.cdma.home.operator.numeric", operator_numeric);
    property_set("ro.telephony.default_cdma_sub", default_cdma_sub);
    property_set("ro.telephony.default_network", default_network);
    set_rild_libpath(rild_lib_variant);

    // Static CDMA Properties
    property_set("ril.subscription.types", "NV,RUIM");
    property_set("telephony.lteOnCdmaDevice", "1");
}

void gsm_properties(const char default_network[],
        char const rild_lib_variant[])
{
    set_rild_libpath(rild_lib_variant);

    // Dynamic GSM Properties
    property_set("ro.telephony.default_network", default_network);

    // Static GSM Properties
    property_set("telephony.lteOnGsmDevice", "1");
}

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[],
        char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}
