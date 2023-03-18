/*
 * Copyright (C) 2018 The Android Open Source Project
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

#ifndef TNT_FILAMENT_BACKEND_OPENGL_OHOS_EXTERNAL_STREAM_MANAGER_OHOS_H
#define TNT_FILAMENT_BACKEND_OPENGL_OHOS_EXTERNAL_STREAM_MANAGER_OHOS_H

#include <backend/Platform.h>

namespace filament::backend {

/*
 * ExternalStreamManagerOHOS::Stream is basically a wrapper for SurfaceTexture.
 *
 * This class DOES DEPEND on having a GLES context, because that's how SurfaceTexture works.
 */
class ExternalStreamManagerOHOS {
public:
    using Stream = Platform::Stream;

    // must be called on GLES thread
    static ExternalStreamManagerOHOS& create() noexcept;

    // must be called on GLES thread
    static void destroy(ExternalStreamManagerOHOS* pExternalStreamManagerOHOS) noexcept;

    // Stream* acquire(jobject surfaceTexture) noexcept;
    void release(Stream* stream) noexcept;

    // attach Stream to current GLES context
    void attach(Stream* stream, intptr_t tname) noexcept;

    // detach Stream to current GLES context
    void detach(Stream* stream) noexcept;

    // must be called on GLES context thread, updates the stream content
    void updateTexImage(Stream* stream, int64_t* timestamp) noexcept;

private:
    ExternalStreamManagerOHOS() noexcept;
    ~ExternalStreamManagerOHOS() noexcept;

};

} // namespace filament::backend

#endif //TNT_FILAMENT_BACKEND_OPENGL_OHOS_EXTERNAL_STREAM_MANAGER_OHOS_H
