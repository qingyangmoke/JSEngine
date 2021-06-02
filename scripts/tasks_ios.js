const path = require('path');
const { task } = require('gulp');
const { execSync } = require('child_process');
const mkdirp = require('mkdirp');
const fs = require('fs');
const PROJECT_ROOT = path.join(__dirname, '..');
const PATH_BUILD = path.join(PROJECT_ROOT, 'build');
const PATH_SOURCE = path.join(PROJECT_ROOT, 'src');
const PATH_TEMPLATE = path.join(PROJECT_ROOT, 'scripts/templates');

const BUILD_MODE = process.env.BUILD_MODE || 'Debug';
const ENABLE_PROFILE = process.env.ENABLE_PROFILE === 'true';
const IS_SIMULATOR = process.env.SIMULATOR == 'IOS';
const BUILD_TYPE = BUILD_MODE == 'Release' ? 'RelWithDebInfo' : 'Debug';

const TARGET_NAME = 'my_bridge';

const JS_ENGINE = process.env.JS_ENGINE || 'jsc';

// generate build scripts for simulator
task('clean-ios-simulator', (done) => {
    execSync(`rm -rf ${PATH_BUILD}/cmake-build-ios-x64`, { stdio: 'inherit' });
    execSync(`rm -rf ${PATH_BUILD}/ios/lib/x86_64`, { stdio: 'inherit' });
    done();
});

task('build-ios-simulator', (done) => {
    console.log('build-ios-simulator-lib');
    execSync(
        `cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
  -DCMAKE_TOOLCHAIN_FILE=${PROJECT_ROOT}/cmake/ios.toolchain.cmake \
  -DPLATFORM=SIMULATOR64 \
  ${ENABLE_PROFILE ? '-DENABLE_PROFILE=TRUE \\' : '\\'}
  -DENABLE_BITCODE=FALSE -G "Unix Makefiles" -B ${PATH_BUILD}/cmake-build-ios-x64 -S ${PATH_SOURCE}`,
        {
            cwd: PATH_BUILD,
            stdio: 'inherit',
            env: {
                ...process.env,
                BRIDGE_JS_ENGINE: JS_ENGINE,
                LIBRARY_OUTPUT_DIR: `${PATH_BUILD}/ios/lib/x86_64`,
            },
        },
    );

    // build for simulator
    execSync(`cmake --build ${PATH_BUILD}/cmake-build-ios-x64 --target ${TARGET_NAME} -- -j 12`, {
        stdio: 'inherit',
    });
    done();
});

task('clean-ios-arm', (done) => {
    execSync(`rm -rf ${PATH_BUILD}/cmake-build-ios-arm`, { stdio: 'inherit' });
    execSync(`rm -rf ${PATH_BUILD}/ios/lib/arm`, { stdio: 'inherit' });
    done();
});

// geneate builds scripts for ARMV7, ARMV7S
task('build-ios-arm', (done) => {
    console.log('build-ios-arm');
    execSync(
        `cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
-DCMAKE_TOOLCHAIN_FILE=${PROJECT_ROOT}/cmake/ios.toolchain.cmake \
-DPLATFORM=OS \
${ENABLE_PROFILE ? '-DENABLE_PROFILE=TRUE \\' : '\\'}
-DENABLE_BITCODE=FALSE -G "Unix Makefiles" -B ${PATH_BUILD}/cmake-build-ios-arm -S ${PATH_SOURCE}`,
        {
            cwd: PATH_BUILD,
            stdio: 'inherit',
            env: {
                ...process.env,
                BRIDGE_JS_ENGINE: JS_ENGINE,
                LIBRARY_OUTPUT_DIR: `${PATH_BUILD}/ios/lib/arm`,
            },
        },
    );

    // build for ARMV7, ARMV7S
    execSync(`cmake --build ${PATH_BUILD}/cmake-build-ios-arm --target ${TARGET_NAME} -- -j 12`, {
        stdio: 'inherit',
    });
    done();
});

task('clean-ios-arm64', (done) => {
    execSync(`rm -rf ${PATH_BUILD}/cmake-build-ios-arm64`, { stdio: 'inherit' });
    execSync(`rm -rf ${PATH_BUILD}/ios/lib/arm64`, { stdio: 'inherit' });
    done();
});

// geneate builds scripts for ARM64
task('build-ios-arm64', (done) => {
    console.log('build-ios-arm');
    execSync(
        `cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
-DCMAKE_TOOLCHAIN_FILE=${PROJECT_ROOT}/cmake/ios.toolchain.cmake \
-DPLATFORM=OS64 \
${ENABLE_PROFILE ? '-DENABLE_PROFILE=TRUE \\' : '\\'}
-DENABLE_BITCODE=FALSE -G "Unix Makefiles" -B ${PATH_BUILD}/cmake-build-ios-arm64 -S ${PATH_SOURCE}`,
        {
            cwd: PATH_BUILD,
            stdio: 'inherit',
            env: {
                ...process.env,
                BRIDGE_JS_ENGINE: JS_ENGINE,
                LIBRARY_OUTPUT_DIR: `${PATH_BUILD}/ios/lib/arm64`,
            },
        },
    );

    // build for ARM64
    execSync(`cmake --build ${PATH_BUILD}/cmake-build-ios-arm64 --target ${TARGET_NAME} -- -j 12`, {
        stdio: 'inherit',
    });
    done();
});

task('copy-ios-framework', (done) => {
    execSync(
        `cp -r ${PATH_BUILD}/ios/framework/${TARGET_NAME}.framework/ ${PROJECT_ROOT}/examples/ios/ioscplus/${TARGET_NAME}.framework`,
        { stdio: 'inherit' },
    );
    done();
});

task('clean-ios', (done) => {
    console.log('clean-android');
    if (!fs.existsSync(`${PATH_BUILD}`)) {
        console.log('not existsSync');
        fs.mkdirSync(`${PATH_BUILD}`);
    } else {
        execSync(`rm -rf ${PATH_BUILD}/ios/framework`, { stdio: 'inherit' });
        mkdirp.sync(`${PATH_BUILD}/ios/framework`);
    }
    done();
});

task('build-ios', (done) => {
    const armDynamicSDKPath = `${PATH_BUILD}/ios/lib/arm/${TARGET_NAME}.framework/${TARGET_NAME}`;
    const arm64DynamicSDKPath = `${PATH_BUILD}/ios/lib/arm64/${TARGET_NAME}.framework/${TARGET_NAME}`;
    const x64DynamicSDKPath = `${PATH_BUILD}/ios/lib/x86_64/${TARGET_NAME}.framework/${TARGET_NAME}`;

    const targetDynamicSDKPath = `${PATH_BUILD}/ios/framework`;
    const frameworkPath = `${targetDynamicSDKPath}/${TARGET_NAME}.framework`;
    const plistPath = path.join(PATH_TEMPLATE, 'Info.plist');
    mkdirp.sync(frameworkPath);
    const linkDynamicSDKPath = IS_SIMULATOR
        ? `${x64DynamicSDKPath} ${armDynamicSDKPath} ${arm64DynamicSDKPath}`
        : `${armDynamicSDKPath} ${arm64DynamicSDKPath}`;
    execSync(`lipo -create ${linkDynamicSDKPath} -output ${frameworkPath}/${TARGET_NAME}`, {
        stdio: 'inherit',
    });
    execSync(`cp ${plistPath} ${frameworkPath}/Info.plist`, { stdio: 'inherit' });
    execSync(
        `cp -r ${PATH_BUILD}/ios/lib/${
            IS_SIMULATOR ? 'x86_64' : 'arm'
        }/${TARGET_NAME}.framework/Headers ${frameworkPath}`,
        { stdio: 'inherit' },
    );
    if (BUILD_MODE == 'Release') {
        execSync(`dsymutil ${frameworkPath}/${TARGET_NAME}`, {
            stdio: 'inherit',
            cwd: targetDynamicSDKPath,
        });
        execSync(`mv ${frameworkPath}/${TARGET_NAME}.dSYM ${targetDynamicSDKPath}`);
        execSync(`strip -S -X -x ${frameworkPath}/${TARGET_NAME}`, {
            stdio: 'inherit',
            cwd: targetDynamicSDKPath,
        });
    }
    done();
});
