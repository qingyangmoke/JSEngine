/**
 * Build script for iOS
 */

 require('./tasks_ios.js');
const chalk = require('chalk');
const { series } = require('gulp');

series(
    'clean-ios-arm',
    'build-ios-arm',
)((err) => {
    if (err) {
        console.log(err);
    } else {
        console.log(chalk.green('Success.'));
    }
});
