/**
 * Build script for iOS
 */

require('./tasks_ios.js');
const chalk = require('chalk');
const { series } = require('gulp');

const IS_SIMULATOR = process.env.SIMULATOR == 'IOS';

const simulatorTasks = IS_SIMULATOR ? ['clean-ios-simulator', 'build-ios-simulator'] : [];
// Run tasks
series(
    'clean-ios',
    ...simulatorTasks,
    ...['clean-ios-arm', 'build-ios-arm', 'clean-ios-arm64', 'build-ios-arm64'],
    'build-ios',
    'copy-ios-framework',
)((err) => {
    if (err) {
        console.log(err);
    } else {
        console.log(chalk.green('Success.'));
    }
});