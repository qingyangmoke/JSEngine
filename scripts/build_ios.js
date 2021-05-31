/**
 * Build script for iOS
 */

const { paths } = require('./tasks');
const chalk = require('chalk');
const path = require('path');
const { program } = require('commander');
// const minimist = require('minimist');
const { series, parallel, task } = require('gulp');
const { execSync } = require('child_process');
const buildMode = process.env.KRAKEN_BUILD || 'Debug';

const IS_SIMULATOR = process.env.SIMULATOR == 'IOS';

const simulatorTasks = IS_SIMULATOR ? ['clean-ios-simulator', 'build-ios-simulator'] : [];
// Run tasks
series(
    ...simulatorTasks,
    ...['clean-ios-arm', 'build-ios-arm', 'clean-ios-arm64', 'build-ios-arm64'],
    'clean-ios',
    'build-ios',
    'copy-ios-framework',
)((err) => {
    if (err) {
        console.log(err);
    } else {
        console.log(chalk.green('Success.'));
    }
});