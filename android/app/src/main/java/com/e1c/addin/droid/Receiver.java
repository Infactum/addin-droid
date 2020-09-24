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
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;

import java.util.HashSet;
import java.util.Set;

public class Receiver extends BroadcastReceiver implements Runnable {
    private long handle;
    private Activity activity;
    private Set<String> actionFilters = new HashSet<String>();
    private boolean isRegistered;

    public Receiver(Activity activity, long handle) {
        this.handle = handle;
        this.activity = activity;
    }

    public void activate() {
        activity.runOnUiThread(this);
    }

    private native void sendEvent(String action);

    @Override
    public void run() {
        System.loadLibrary("Droid");
    }

    public void addFilter(String action) {
        actionFilters.add(action);
    }

    public void clearFilters() {
        actionFilters.clear();
    }

    public void register() {
        unregister();
        IntentFilter filter = new IntentFilter();
        actionFilters.forEach(filter::addAction);
        activity.registerReceiver(this, filter);
        isRegistered = true;
    }

    public void unregister() {
        if (isRegistered) {
            activity.unregisterReceiver(this);
            isRegistered = false;
        }
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        String action = intent.getAction();
        if (action == null)
            return;
        sendEvent(action);
    }
}
