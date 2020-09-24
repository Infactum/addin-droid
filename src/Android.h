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

#ifndef ANDROID_H
#define ANDROID_H

#include <functional>

#include <jni.h>

#include "AndroidCallback.h"
#include "IAndroid.h"

/* Inheritance Order matters here */
class Android : public IAndroid {
public:
    Android(jclass loc_clazz, jobject activity, std::unique_ptr<AndroidCallback> callback);

    virtual ~Android();

    void AddFilter(const std::string &action) override;

    void ClearFilters() override;

    void Register() override;

    void Unregister() override { unregister(); };

private:
    void unregister();

    std::unique_ptr<AndroidCallback> cb;
    jclass clazz;
    jobject obj;
    jmethodID add_filter_id;
    jmethodID clear_filter_id;
    jmethodID register_id;
    jmethodID unregister_id;
};


#endif //ANDROID_H
