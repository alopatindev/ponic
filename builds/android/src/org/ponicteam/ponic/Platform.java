package org.ponicteam.ponic;

public class Platform {

     static {
         System.loadLibrary("ponic");
     }

     public static native void init(int width, int height);
     public static native void step();
     public static native void onCreateJNI(String resourcesLocation);
}
