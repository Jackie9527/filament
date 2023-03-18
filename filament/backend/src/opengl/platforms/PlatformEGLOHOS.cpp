/*
 * Copyright (C) 2019 The Android Open Source Project
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

#include <backend/platforms/PlatformEGLOHOS.h>

#include "opengl/GLUtils.h"
#include "ExternalStreamManagerOHOS.h"



#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <utils/compiler.h>
#include <utils/Log.h>


// We require filament to be built with an API 19 toolchain, before that, OpenGLES 3.0 didn't exist
// Actually, OpenGL ES 3.0 was added to API 18, but API 19 is the better target and
// the minimum for Jetpack at the time of this comment.

using namespace utils;

namespace filament::backend {
using namespace backend;

// The OHOS NDK doesn't expose extensions, fake it with eglGetProcAddress
namespace glext {

extern PFNEGLCREATESYNCKHRPROC eglCreateSyncKHR;
extern PFNEGLDESTROYSYNCKHRPROC eglDestroySyncKHR;
extern PFNEGLCLIENTWAITSYNCKHRPROC eglClientWaitSyncKHR;
extern PFNEGLCREATEIMAGEKHRPROC eglCreateImageKHR;
extern PFNEGLDESTROYIMAGEKHRPROC eglDestroyImageKHR;

#if 0
UTILS_PRIVATE PFNEGLGETNATIVECLIENTBUFFEROHOSPROC eglGetNativeClientBufferOHOS = {};
UTILS_PRIVATE PFNEGLPRESENTATIONTIMEOHOSPROC eglPresentationTimeOHOS = {};
UTILS_PRIVATE PFNEGLGETCOMPOSITORTIMINGSUPPORTEDOHOSPROC eglGetCompositorTimingSupportedOHOS = {};
UTILS_PRIVATE PFNEGLGETCOMPOSITORTIMINGOHOSPROC eglGetCompositorTimingOHOS = {};
UTILS_PRIVATE PFNEGLGETNEXTFRAMEIDOHOSPROC eglGetNextFrameIdOHOS = {};
UTILS_PRIVATE PFNEGLGETFRAMETIMESTAMPSUPPORTEDOHOSPROC eglGetFrameTimestampSupportedOHOS = {};
UTILS_PRIVATE PFNEGLGETFRAMETIMESTAMPSOHOSPROC eglGetFrameTimestampsOHOS = {};
#endif
}
using namespace glext;

using EGLStream = Platform::Stream;

// ---------------------------------------------------------------------------------------------

PlatformEGLOHOS::PlatformEGLOHOS() noexcept
        : PlatformEGL(),
          mExternalStreamManager(ExternalStreamManagerOHOS::create()) {

}

PlatformEGLOHOS::~PlatformEGLOHOS() noexcept = default;


void PlatformEGLOHOS::terminate() noexcept {
    ExternalStreamManagerOHOS::destroy(&mExternalStreamManager);
    PlatformEGL::terminate();
}

Driver* PlatformEGLOHOS::createDriver(void* sharedContext,
        const Platform::DriverConfig& driverConfig) noexcept {
    Driver* driver = PlatformEGL::createDriver(sharedContext, driverConfig);
#if 0
    auto extensions = GLUtils::split(eglQueryString(mEGLDisplay, EGL_EXTENSIONS));

    eglGetNativeClientBufferOHOS = (PFNEGLGETNATIVECLIENTBUFFEROHOSPROC) eglGetProcAddress(
            "eglGetNativeClientBufferOHOS");

    if (extensions.has("EGL_OHOS_presentation_time")) {
        eglPresentationTimeOHOS = (PFNEGLPRESENTATIONTIMEOHOSPROC)eglGetProcAddress(
                "eglPresentationTimeOHOS");
    }

    if (extensions.has("EGL_OHOS_get_frame_timestamps")) {
        eglGetCompositorTimingSupportedOHOS = (PFNEGLGETCOMPOSITORTIMINGSUPPORTEDOHOSPROC)eglGetProcAddress(
                "eglGetCompositorTimingSupportedOHOS");
        eglGetCompositorTimingOHOS = (PFNEGLGETCOMPOSITORTIMINGOHOSPROC)eglGetProcAddress(
                "eglGetCompositorTimingOHOS");
        eglGetNextFrameIdOHOS = (PFNEGLGETNEXTFRAMEIDOHOSPROC)eglGetProcAddress(
                "eglGetNextFrameIdOHOS");
        eglGetFrameTimestampSupportedOHOS = (PFNEGLGETFRAMETIMESTAMPSUPPORTEDOHOSPROC)eglGetProcAddress(
                "eglGetFrameTimestampSupportedOHOS");
        eglGetFrameTimestampsOHOS = (PFNEGLGETFRAMETIMESTAMPSOHOSPROC)eglGetProcAddress(
                "eglGetFrameTimestampsOHOS");
    }
#endif
    return driver;
}

void PlatformEGLOHOS::setPresentationTime(int64_t presentationTimeInNanosecond) noexcept {
#if 0
    if (mCurrentDrawSurface != EGL_NO_SURFACE) {
        if (eglPresentationTimeOHOS) {
            eglPresentationTimeOHOS(
                    mEGLDisplay,
                    mCurrentDrawSurface,
                    presentationTimeInNanosecond);
        }
    }
#endif
}

Platform::Stream* PlatformEGLOHOS::createStream(void* nativeStream) noexcept {
#if 0
    return mExternalStreamManager.acquire(static_cast<jobject>(nativeStream));
#endif
    return nullptr;
}

void PlatformEGLOHOS::destroyStream(Platform::Stream* stream) noexcept {
    mExternalStreamManager.release(stream);
}

void PlatformEGLOHOS::attach(Stream* stream, intptr_t tname) noexcept {
    mExternalStreamManager.attach(stream, tname);
}

void PlatformEGLOHOS::detach(Stream* stream) noexcept {
    mExternalStreamManager.detach(stream);
}

void PlatformEGLOHOS::updateTexImage(Stream* stream, int64_t* timestamp) noexcept {
    mExternalStreamManager.updateTexImage(stream, timestamp);
}

int PlatformEGLOHOS::getOSVersion() const noexcept {
    return mOSVersion;
}

AcquiredImage PlatformEGLOHOS::transformAcquiredImage(AcquiredImage source) noexcept {
#if 0
    // Convert the AHardwareBuffer to EGLImage.
    EGLClientBuffer clientBuffer = eglGetNativeClientBufferOHOS((const AHardwareBuffer*)source.image);
    if (!clientBuffer) {
        slog.e << "Unable to get EGLClientBuffer from AHardwareBuffer." << io::endl;
        return {};
    }
    // Note that this cannot be used to stream protected video (for now) because we do not set EGL_PROTECTED_CONTENT_EXT.
    EGLint attrs[] = { EGL_NONE, EGL_NONE };
    EGLImageKHR eglImage = eglCreateImageKHR(mEGLDisplay, EGL_NO_CONTEXT, EGL_NATIVE_BUFFER_OHOS, clientBuffer, attrs);
    if (eglImage == EGL_NO_IMAGE_KHR) {
        slog.e << "eglCreateImageKHR returned no image." << io::endl;
        return {};
    }

    // Destroy the EGLImage before invoking the user's callback.
    struct Closure {
        Closure(AcquiredImage const& acquiredImage, EGLDisplay display)
                : acquiredImage(acquiredImage), display(display) {}
        AcquiredImage acquiredImage;
        EGLDisplay display;
    };
    Closure* closure = new Closure(source, mEGLDisplay);
    auto patchedCallback = [](void* image, void* userdata) {
        Closure* closure = (Closure*)userdata;
        if (eglDestroyImageKHR(closure->display, (EGLImageKHR) image) == EGL_FALSE) {
            slog.e << "eglDestroyImageKHR failed." << io::endl;
        }
        closure->acquiredImage.callback(closure->acquiredImage.image, closure->acquiredImage.userData);
        delete closure;
    };

    return { eglImage, patchedCallback, closure, source.handler };
#endif
    return {};
}

} // namespace filament::backend

// ---------------------------------------------------------------------------------------------
