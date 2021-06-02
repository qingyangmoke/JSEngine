/**
 * Build script for iOS
 */

require('./tasks_android');
const chalk = require('chalk');
const { series } = require('gulp');

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
