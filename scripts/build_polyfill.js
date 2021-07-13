/**
 * Build script for iOS
 */

require('./tasks_polyfill.js');
const chalk = require('chalk');
const { series } = require('gulp');

series(
    'clean-polyfill',
    'build-polyfill',
)((err) => {
    if (err) {
        console.log(err);
    } else {
        console.log(chalk.green('Success.'));
    }
});
