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

#include <jni.h>

#include "AndroidCallback.h"

class AddInStub {
public:
    AddInStub() {
        cb = new AndroidCallback(
                [this](const std::string &, const std::string &) {
                    events++;
                });
    }

    virtual ~AddInStub() {
        delete cb;
    }

    int EventsCount() { return events; };

    AndroidCallback *callback() { return cb; }

private:
    AndroidCallback *cb;
    int events{0};
};

extern "C"
JNIEXPORT jlong JNICALL
Java_com_e1c_addin_droid_FakeAddIn_stub(JNIEnv *env, jclass clazz) {
    return reinterpret_cast<jlong>(new AddInStub);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_e1c_addin_droid_FakeAddIn_handle(JNIEnv *env, jclass clazz, jlong stub) {
    auto stub_ = reinterpret_cast<AddInStub *>(stub);
    return reinterpret_cast<jlong>(stub_->callback());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_e1c_addin_droid_FakeAddIn_release(JNIEnv *env, jclass thiz, jlong handle) {
    delete reinterpret_cast<AddInStub *>(handle);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_e1c_addin_droid_FakeAddIn_events(JNIEnv *env, jobject thiz) {
    jclass cls = env->GetObjectClass(thiz);
    jfieldID fid = env->GetFieldID(cls, "stub", "J");
    auto stub = reinterpret_cast<AddInStub *>(env->GetLongField(thiz, fid));
    return stub->EventsCount();
}
