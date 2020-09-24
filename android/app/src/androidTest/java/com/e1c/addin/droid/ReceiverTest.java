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

import android.content.Context;
import android.content.Intent;

import androidx.test.core.app.ActivityScenario;
import androidx.test.ext.junit.rules.ActivityScenarioRule;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;

import static org.junit.Assert.*;

@RunWith(AndroidJUnit4.class)
public class ReceiverTest {
    @Rule
    public ActivityScenarioRule<DummyActivity> rule
            = new ActivityScenarioRule<>(DummyActivity.class);

    private FakeAddIn addIn;
    @Mock
    private Context context;

    @Before
    public void setUp() {
        addIn = new FakeAddIn();
    }

    @Test
    public void should_callback_on_event() {
        ActivityScenario<DummyActivity> scenario = rule.getScenario();

        scenario.onActivity(activity -> {
            Receiver receiver = addIn.Load(activity);
            receiver.activate();
            Intent intent = new Intent(Intent.ACTION_SCREEN_ON);
            receiver.onReceive(context, intent);
            assertEquals(1, addIn.events());
        });
    }
}
