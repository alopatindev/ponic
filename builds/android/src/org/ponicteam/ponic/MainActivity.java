package org.ponicteam.ponic;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;


public class MainActivity extends Activity {

    GLView mView;

    @Override protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        mView = new GLView(getApplication());
        setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
}
