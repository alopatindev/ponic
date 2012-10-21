package org.ponicteam.ponic;

import android.app.Activity;
import android.content.res.Resources;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;
import java.io.InputStream;
import java.io.FileOutputStream;
import java.util.zip.*;

import org.ponicteam.ponic.Platform;

public class MainActivity extends Activity {
    public static MainActivity instance;
    public static String LOG_TAG = "Ponic";

    String resourcesLocation;
    GLView mView;

    @Override protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        instance = this;

        String sdPath = Environment.getExternalStorageDirectory()
                                   .getAbsolutePath();
        String packageName = getApplicationContext().getPackageName();
        resourcesLocation = sdPath + "/Android/data/" + packageName + "/";

        unpackResources();

        mView = new GLView(getApplication());
        setContentView(mView);

        Platform.onCreateJNI(resourcesLocation);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }

    public static void LOGI(final String text) { Log.i(LOG_TAG, text); }

    public String getResourcesLocation()
    {
        return resourcesLocation;
    }

    void unpackResources()
    {
        final Resources resources = getApplicationContext().getResources();
        String location = getResourcesLocation();
        LOGI("unpackResources: '" + location + "'");
        try {
            InputStream is = resources.openRawResource(R.raw.res);
            ZipInputStream zis = new ZipInputStream(is);
            ZipEntry ze = null;
            byte[] buffer = new byte[1024];

            while ((ze = zis.getNextEntry()) != null) {
                String filename = location + "/" + ze.getName();
                LOGI(filename);
                if (ze.isDirectory()) {
                    (new File(filename)).mkdirs();
                } else {
                    FileOutputStream fout = new FileOutputStream(filename);
                    int count;
                    while ((count = zis.read(buffer)) != -1)
                        fout.write(buffer, 0, count);
                    fout.close();
                }
                zis.closeEntry();
            }
            zis.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
