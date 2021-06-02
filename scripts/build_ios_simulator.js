/**
 * Build script for iOS
 */

require('./tasks_ios.js');
const chalk = require('chalk');
const { series } = require('gulp');

series(
    'clean-ios-simulator',
    'build-ios-simulator',
    'copy-ios-framework',
)((err) => {
    if (err) {
        console.log(err);
    } else {
        console.log(chalk.green('Success.'));
    }
});
