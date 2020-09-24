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

#include "Android.h"

#include <utility>

#include <jni.h>

#include "jnienv.h"

AndroidCallback *callback(JNIEnv *env, jobject thiz) {
    jclass cls = env->GetObjectClass(thiz);
    jfieldID fid = env->GetFieldID(cls, "handle", "J");
    auto cb = reinterpret_cast<AndroidCallback *>(env->GetLongField(thiz, fid));
    return cb;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_e1c_addin_droid_Receiver_sendEvent(JNIEnv *env, jobject thiz, jstring action) {
    const char *chars = env->GetStringUTFChars(action, nullptr);
    std::string msg{chars};
    callback(env, thiz)->OnEvent(msg, "");
    env->ReleaseStringUTFChars(action, chars);
}

Android::Android(jclass loc_clazz, jobject activity, std::unique_ptr<AndroidCallback> callback)
        : cb(std::move(callback)) {
    JNIEnv *env = getJniEnv();
    clazz = reinterpret_cast<jclass>(env->NewGlobalRef(loc_clazz));

    jmethodID ctor_id = env->GetMethodID(clazz, "<init>", "(Landroid/app/Activity;J)V");
    jobject obj_loc = env->NewObject(clazz, ctor_id, activity,
                                     reinterpret_cast<jlong>(cb.get()));
    obj = env->NewGlobalRef(obj_loc);
    env->DeleteLocalRef(obj_loc);

    jmethodID activate_id = env->GetMethodID(clazz, "activate", "()V");
    env->CallVoidMethod(obj, activate_id);

    add_filter_id = env->GetMethodID(loc_clazz, "addFilter", "(Ljava/lang/String;)V");
    clear_filter_id = env->GetMethodID(loc_clazz, "clearFilters", "()V");
    register_id = env->GetMethodID(loc_clazz, "register", "()V");
    unregister_id = env->GetMethodID(loc_clazz, "unregister", "()V");
}

Android::~Android() {
    unregister();
    JNIEnv *env = getJniEnv();
    env->DeleteGlobalRef(obj);
    env->DeleteGlobalRef(clazz);
}

void Android::AddFilter(const std::string &action) {
    JNIEnv *env = getJniEnv();
    jstring action_ = env->NewStringUTF(action.c_str());
    env->CallVoidMethod(obj, add_filter_id, action_);
    env->DeleteLocalRef(action_);
}

void Android::ClearFilters() {
    getJniEnv()->CallVoidMethod(obj, clear_filter_id);
}

void Android::Register() {
    getJniEnv()->CallVoidMethod(obj, register_id);
}

void Android::unregister() {
    getJniEnv()->CallVoidMethod(obj, unregister_id);
}
