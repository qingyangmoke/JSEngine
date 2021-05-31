/**
 * Build script for iOS
 */

const { paths } = require('./tasks_android');
const chalk = require('chalk');
const path = require('path');
const { program } = require('commander');
const { series, parallel, task } = require('gulp');
const { execSync } = require('child_process');
const buildMode = process.env.KRAKEN_BUILD || 'Debug';

// Run tasks
series(
    'clean-android',
    'build-android',
    'build-android-jni',
    'copy-android-framework',
)((err) => {
    if (err) {
        console.log(err);
    } else {
        console.log(chalk.green('Success.'));
    }
});
