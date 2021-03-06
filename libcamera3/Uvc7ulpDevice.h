/*
 * Copyright (C) 2012-2015 Freescale Semiconductor, Inc.
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

#ifndef _UVC_7ULP_DEVICE_H
#define _UVC_7ULP_DEVICE_H

#include "Camera.h"
#include "MMAPStream.h"

class Uvc7ulpDevice : public Camera
{
public:
    Uvc7ulpDevice(int32_t id, int32_t facing, int32_t orientation,
              char* path, bool createStream = true);
    virtual ~Uvc7ulpDevice();

    static Camera* newInstance(int32_t id, char* name, int32_t facing,
                               int32_t orientation, char* path);

    virtual status_t initSensorStaticData();
    virtual bool isHotplug() {return true;}

protected:
    class Uvc7ulpStream : public MMAPStream {
    public:
        Uvc7ulpStream(Camera* device, const char* name)
              : MMAPStream(device) {
            strncpy(mUvcPath, name, CAMAERA_FILENAME_LENGTH-1);
        }
        virtual ~Uvc7ulpStream() {}

        // configure device.
        virtual int32_t onDeviceConfigureLocked();
        // start device.
        virtual int32_t onDeviceStartLocked();
        // stop device.
        virtual int32_t onDeviceStopLocked();
        // get buffer from V4L2.
        virtual int32_t onFrameAcquireLocked();
        // put buffer back to V4L2.
        virtual int32_t onFrameReturnLocked(int32_t index, StreamBuffer& buf);

        // get device buffer required size.
        virtual int32_t getDeviceBufferSize();

    protected:
        char mUvcPath[CAMAERA_FILENAME_LENGTH];
    };
};

class LogitC920 : public Uvc7ulpDevice
{
public:
    LogitC920(int32_t id, int32_t facing, int32_t orientation, char* path);
    virtual ~LogitC920();

    virtual status_t initSensorStaticData();

private:
    class C920Stream : public Uvc7ulpDevice::Uvc7ulpStream {
    public:
        C920Stream(Camera* device, const char* name);
        virtual ~C920Stream();

        // start device.
        virtual int32_t onDeviceStartLocked();
        // get buffer from V4L2.
        virtual int32_t onFrameAcquireLocked();

        void setOmitSize(uint32_t width, uint32_t height);

    private:
        uint32_t mOmitFrames;
        uint32_t mOmitFrameCnt;
        uint32_t mOmitFrameWidth;
        uint32_t mOmitFrameHeight;
    };

    C920Stream* mC920Stream;
};

#endif
