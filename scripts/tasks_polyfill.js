const path = require('path');
const { task } = require('gulp');
const { execSync } = require('child_process');
const os = require('os');
const fs = require('fs');
const webpack = require('webpack');
const webpackConfig = require('../webpack.config');

const PROJECT_ROOT = path.join(__dirname, '..');
const PATH_BUILD = path.join(PROJECT_ROOT, 'build');
const PATH_SOURCE = path.join(PROJECT_ROOT, 'src');

task('clean-polyfill', (done) => {
    console.log('clean-polyfill');
    if (!fs.existsSync(`${PATH_BUILD}`)) {
        console.log('not existsSync');
        fs.mkdirSync(`${PATH_BUILD}`);
    } else {
        console.log('existsSync');
        execSync(`rm -rf ${path.join(PATH_BUILD, 'polyfill')}`, { stdio: 'inherit' });
    }
    done();
});

task('build-polyfill', (done) => {
    console.log('build-polyfill');
    // 构建js 
    webpack(webpackConfig, (err, stats) => {
        if (err || stats.hasErrors()) {
            // 在这里处理错误
        }
        console.log(err);
        console.log(stats.compilation.errors);

        // 构建c++ .cc
        let jsCode = JSON.stringify(
            fs.readFileSync(path.join(PATH_BUILD, 'polyfill/DomPolyfill.js'), {
                encoding: 'utf-8',
            }),
        );

        fs.writeFileSync(
            path.join(PATH_SOURCE, 'core/plugins/dom/DomPolyfill.cc'),
            `#include "DomPolyfill.h"
void injectDomPolyfill(JSEngineNS::EngineScope *scope)
{
    scope->evaluateJavaScript(${jsCode}, "internal://polyfill", 0);
}`,
        );
        done();
    });
});
