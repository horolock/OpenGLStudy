package com.example.bluegl

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyGLRenderer : GLSurfaceView.Renderer {
    external fun nativeInit()
    external fun nativeResize(width: Int, height: Int)
    external fun nativeRender()

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        nativeInit()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        nativeResize(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        nativeRender()
    }

    companion object {
        init {
            System.loadLibrary("bluegl-native")
        }
    }
}