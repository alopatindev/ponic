extern "C" {
    #include <jni.h>
}

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Log.h"
#include "System.h"
#include "ImageManager.h"

bool setupGraphics(int w, int h) {
    LOGI("setupGraphics(%d, %d)", w, h);
    glViewport(0, 0, w, h);
    return true;
}

void renderFrame() {
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
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
    ImageManager::getInstance().parseAtlasXML("atlases/atlasDictionary.xml");
    ImageManager::getInstance().loadGroup("game_common");

    //FIXME: ReleaseStringUTFChars
}
