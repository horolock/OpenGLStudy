package com.example.bluegl

import android.content.Context
import android.opengl.GLSurfaceView

class MyGLSurfaceView(context: Context) : GLSurfaceView(context) {
    private val renderer: MyGLRenderer

    init {
        // Use OpenGL ES 2.0
        setEGLContextClientVersion(2)
        renderer = MyGLRenderer()
        setRenderer(renderer)

        // Keep rendering
        renderMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY

    }
}