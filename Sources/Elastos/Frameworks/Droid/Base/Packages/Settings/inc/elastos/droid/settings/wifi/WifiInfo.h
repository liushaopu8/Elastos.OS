/*
 * Copyright (C) 2009 The Android Open Source Project
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

package com.android.settings.wifi;

using Elastos::Droid::Settings::IR;

using Elastos::Droid::Os::IBundle;
using Elastos::Droid::Preference::IPreferenceActivity;


/**
 * Wifi information menu item on the diagnostic screen
 */
public class WifiInfo extends PreferenceActivity {

    //@Override
    protected void OnCreate(Bundle savedInstanceState) {
        super->OnCreate(savedInstanceState);
        AddPreferencesFromResource(R.xml.testing_wifi_settings);
    }

}
