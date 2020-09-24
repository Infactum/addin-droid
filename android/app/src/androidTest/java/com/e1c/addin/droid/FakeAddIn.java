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

package com.e1c.addin.droid;

import android.app.Activity;

public class FakeAddIn {
    static {
        System.loadLibrary("Droid");
    }

    private long stub;
    private long handle;

    private static native long stub();

    private static native long handle(long stub);

    private static native void release(long handle);

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        release(stub);
    }

    public FakeAddIn() {
        this.stub = stub();
        this.handle = handle(stub);
    }

    public native int events();

    public Receiver Load(Activity activity) {
        return new Receiver(activity, handle);
    }
}
