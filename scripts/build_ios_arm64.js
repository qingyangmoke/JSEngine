/**
 * Build script for iOS
 */

 require('./tasks_ios.js');
const chalk = require('chalk');
const { series } = require('gulp');

series(
    'clean-ios-arm64',
    'build-ios-arm64',
)((err) => {
    if (err) {
        console.log(err);
    } else {
        console.log(chalk.green('Success.'));
    }
});
