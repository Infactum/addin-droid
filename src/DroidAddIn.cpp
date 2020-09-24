/*
 *  addin-droid
 *  Copyright (C) 2020  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "DroidAddIn.h"

#ifdef __ANDROID__

#include "jnienv.h"

#include "Android.h"

#endif

DroidAddIn::DroidAddIn() {
    AddMethod(L"AddFilter", L"ДобавитьФильтр", this, &DroidAddIn::addFilter);
    AddMethod(L"ClearFilters", L"ОчиститьФильтры", this, &DroidAddIn::clearFilters);
    AddMethod(L"Register", L"Зарегистрировать", this, &DroidAddIn::registerReceiver);
    AddMethod(L"Unregister", L"ОтменитьРегистрацию", this, &DroidAddIn::unregisterReceiver);

    AddProperty(L"ErrorInfo", L"ОписаниеОшибки", [&]() {
        return std::make_shared<variant_t>(error_info);
    });
}

void DroidAddIn::addFilter(const variant_t &action) {
    if (!ext)
        initExtension();
    const auto &action_ = std::get<std::string>(action);
    ext->AddFilter(action_);
}

void DroidAddIn::clearFilters() {
    if (!ext)
        initExtension();
    ext->ClearFilters();
}

void DroidAddIn::registerReceiver() {
    if (!ext)
        initExtension();
    ext->Register();
}

void DroidAddIn::unregisterReceiver() {
    if (!ext)
        initExtension();
    ext->Unregister();
}

void DroidAddIn::initExtension() {
#ifndef __ANDROID__
    error_info = "Current OS is not supported";
    throw std::runtime_error(error_info);
#else
    auto activity = GetActivity();
    auto clazz = FindClass("com/e1c/addin/droid/Receiver");
    if (!clazz) {
        error_info = "Failed to find JVM class";
        throw std::runtime_error(error_info);
    }
    auto cb = std::make_unique<AndroidCallback>(
            [this](const std::string &msg, const std::string &data) {
                ExternalEvent("com.e1c.addin.droid.Receiver", msg, data);
            });
    ext = std::make_unique<Android>(clazz, activity, std::move(cb));
#endif
}
