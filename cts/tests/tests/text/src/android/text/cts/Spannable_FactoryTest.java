/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package android.text.cts;

import android.test.AndroidTestCase;
import android.text.Spannable;
import android.text.SpannableString;
import android.text.Spannable.Factory;
import dalvik.annotation.TestLevel;
import dalvik.annotation.TestTargetClass;
import dalvik.annotation.TestTargetNew;
import dalvik.annotation.ToBeFixed;

@TestTargetClass(Factory.class)
public class Spannable_FactoryTest extends AndroidTestCase {

    @TestTargetNew(
        level = TestLevel.COMPLETE,
        method = "newSpannable",
        args = {java.lang.CharSequence.class}
    )
    @ToBeFixed(bug="1695243", explanation="should add @throws clause into javadoc of "
        + "Spannable.Factory#newSpannable(CharSequence) when param CharSequence is null")
    public void testNewSpannable() {
        final String text = "test newSpannable";
        Factory factory = Spannable.Factory.getInstance();

        Spannable spannable = factory.newSpannable(text);
        assertNotNull(spannable);
        assertTrue(spannable instanceof SpannableString);
        assertEquals(text, spannable.toString());

        try {
            factory.newSpannable(null);
            fail("should throw NullPointerException here");
        } catch (NullPointerException e) {
        }
    }

    @TestTargetNew(
        level = TestLevel.COMPLETE,
        method = "getInstance",
        args = {}
    )
    public void testGetInstance() {
        Spannable.Factory factory = Spannable.Factory.getInstance();
        assertNotNull(factory);
        assertSame(factory, Spannable.Factory.getInstance());
    }
}
