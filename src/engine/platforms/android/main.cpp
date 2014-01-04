extern "C" {
    #include <jni.h>
}

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Log.h"
#include "System.h"
#include "ImageManager.h"
#include "Graphics.h"

bool setupGraphics(int w, int h) {
    LOGI("setupGraphics(%d, %d)", w, h);
    glViewport(0, 0, w, h);
    return true;
}

void renderFrame() {
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
//    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


    GRAPHICS.startFrame();
    GRAPHICS.drawRectangle2D(0.0f, 0.0f,
                             1.0f, 1.0f,
                             0.0f, 0.5f, 0.5f, 0.7f);
    GRAPHICS.endFrame();
}

extern "C" {
    JNIEXPORT void JNICALL Java_org_ponicteam_ponic_Platform_init(
        JNIEnv* env, jobject obj,  jint width, jint height
    );
    JNIEXPORT void JNICALL Java_org_ponicteam_ponic_Platform_step(
        JNIEnv* env, jobject obj
    );
    JNIEXPORT void JNICALL Java_org_ponicteam_ponic_Platform_onCreateJNI(
        JNIEnv* env, jobject obj,  jstring resourcesLocation
    );
};

JNIEXPORT void JNICALL Java_org_ponicteam_ponic_Platform_init(
    JNIEnv* env, jobject obj,  jint width, jint height
)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_org_ponicteam_ponic_Platform_step(
    JNIEnv* env, jobject obj
)
{
    renderFrame();
}

JNIEXPORT void JNICALL Java_org_ponicteam_ponic_Platform_onCreateJNI(
    JNIEnv* env, jobject obj,  jstring resourcesLocation
)
{
    const char *loc = env->functions->GetStringUTFChars(env, resourcesLocation, NULL);
    SYSTEM.setResourcesPath(loc);
    ImageManager::get().parseAtlasXML("atlases/atlasDictionary.xml");
    ImageManager::get().loadGroup("game_common");

    GRAPHICS.init();

    //FIXME: ReleaseStringUTFChars
}
