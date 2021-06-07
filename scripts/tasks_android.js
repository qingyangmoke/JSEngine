const path = require('path');
const { task } = require('gulp');
const { execSync } = require('child_process');
const os = require('os');
const fs = require('fs');

const OS_PLATFORM = os.platform();

const PROJECT_ROOT = path.join(__dirname, '..');
const PATH_BUILD = path.join(PROJECT_ROOT, 'build');
const PATH_SOURCE = path.join(PROJECT_ROOT, 'src');

const BUILD_MODE = process.env.BUILD_MODE || 'Debug';
const IS_SIMULATOR = process.env.SIMULATOR == 'Android';
const BUILD_TYPE = BUILD_MODE == 'Release' ? 'RelWithDebInfo' : 'Debug';

const TARGET_NAME = 'jsengine_bridge';
const JS_ENGINE_JSC = 'jsc';
const JS_ENGINE_V8 = 'v8';
const JS_ENGINE_QJS = 'quickjs';

const JS_ENGINE = process.env.JS_ENGINE || JS_ENGINE_JSC;

const CMAKE_GENERATOR_TEMPLATE = OS_PLATFORM == 'win32' ? 'Ninja' : 'Unix Makefiles';

const ANDROID_ABI_LIST = ['arm64-v8a', 'armeabi-v7a', 'x86_64'];

let ANDROID_HOME_PATH;

if (OS_PLATFORM == 'win32') {
    ANDROID_HOME_PATH = path.join(process.env.LOCALAPPDATA, 'Android\\Sdk');
} else {
    ANDROID_HOME_PATH = path.join(process.env.HOME, 'Library/Android/sdk');
}

const ndkDir = path.join(ANDROID_HOME_PATH, 'ndk');
let installedNDK = fs.readdirSync(ndkDir).filter((d) => d[0] != '.');
if (installedNDK.length == 0) {
    throw new Error('Android NDK not Found. Please install one');
}
const NDK_VERSION = installedNDK.slice(-1)[0];
if (parseInt(NDK_VERSION.substr(0, 2)) < 20) {
    throw new Error('Android NDK version must at least >= 20');
}

const CMAKE_TOOLCHAIN_FILE = path.join(
    ANDROID_HOME_PATH,
    'ndk',
    NDK_VERSION,
    '/build/cmake/android.toolchain.cmake',
);
const ANDROID_NDK = path.join(ANDROID_HOME_PATH, '/ndk/', NDK_VERSION);

task('clean-android', (done) => {
    console.log('clean-android');
    if (!fs.existsSync(`${PATH_BUILD}`)) {
        console.log('not existsSync');
        fs.mkdirSync(`${PATH_BUILD}`);
    } else {
        console.log('existsSync');
        execSync(`rm -rf ${PATH_BUILD}/android`, { stdio: 'inherit' });
        ANDROID_ABI_LIST.forEach((e) => {
            execSync(`rm -rf ${PATH_BUILD}/cmake-build-android-${e}`, { stdio: 'inherit' });
        });
    }
    done();
});

task('build-android', (done) => {
    console.log('build-android');
    ANDROID_ABI_LIST.forEach((arch) => {
        console.log('build-android arch=', arch);
        const LIBRARY_OUTPUT_DIR = path.join(PATH_BUILD, `android/jni/libs/${arch}`);
        const currentCmakeDir = path.join(PATH_BUILD, `cmake-build-android-${arch}`);
        execSync(
            `cmake  -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
                    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} \
                    -DANDROID_NDK=${ANDROID_NDK} \
                    -DIS_ANDROID=TRUE \
                    -DANDROID_ABI="${arch}" \
                    -DANDROID_PLATFORM="android-16" \
                    -DANDROID_STL=c++_shared \
                    -G "${CMAKE_GENERATOR_TEMPLATE}" \
                    -B ${currentCmakeDir} -S ${PATH_SOURCE}`,
            {
                cwd: PATH_BUILD,
                stdio: 'inherit',
                env: {
                    ...process.env,
                    BRIDGE_JS_ENGINE: JS_ENGINE,
                    LIBRARY_OUTPUT_DIR: LIBRARY_OUTPUT_DIR,
                },
            },
        );

        // build
        execSync(`cmake --build ${currentCmakeDir} --target ${TARGET_NAME} -- -j 12`, {
            stdio: 'inherit',
        });

        switch (JS_ENGINE) {
            case JS_ENGINE_JSC:
                execSync(
                    `cp -r ${PROJECT_ROOT}/third_party/JavaScriptCore/lib/android/${arch}/ ${LIBRARY_OUTPUT_DIR}`,
                    { stdio: 'inherit' },
                );
                break;
        }
    });
    done();
});

task('clean-android-jni', (done) => {
    execSync(`rm -rf ${PROJECT_ROOT}/examples/android/app/libs`, { stdio: 'inherit' });
    done();
});

task('build-android-jni', (done) => {
    console.log('build-android-jni');
    execSync(`cp -r ${PATH_SOURCE}/jni/ ${PATH_BUILD}/android/jni`, { stdio: 'inherit' });
    execSync(`cp -r ${PATH_SOURCE}/include/ ${PATH_BUILD}/android/jni/include`, {
        stdio: 'inherit',
    });

    execSync(
        `${ANDROID_NDK}/ndk-build NDK_PROJECT_PATH=./ NDK_APPLICATION_MK=./jni/Application.mk APP_BUILD_SCRIPT=./jni/Android.mk`,
        {
            cwd: `${PATH_BUILD}/android`,
            stdio: 'inherit',
        },
    );

    switch (JS_ENGINE) {
        case JS_ENGINE_JSC:
            ANDROID_ABI_LIST.forEach((arch) => {
                execSync(
                    `cp -r ${PROJECT_ROOT}/third_party/JavaScriptCore/lib/android/${arch}/ ${PATH_BUILD}/android/libs/${arch}`,
                    { stdio: 'inherit' },
                );
            });
            break;
    }
    done();
});

task('copy-android-framework', (done) => {
    execSync(`cp -r ${PATH_BUILD}/android/libs/ ${PROJECT_ROOT}/examples/android/app/libs`, {
        stdio: 'inherit',
    });
    done();
});
