const path = require('path');

module.exports = {
    entry: './src/core/plugins/dom/polyfill/index.ts',
    // devtool: 'inline-source-map',
    mode: 'production',
    module: {
        rules: [
            {
                test: /\.tsx?$/,
                use: 'ts-loader',
                exclude: /node_modules/,
            },
        ],
    },
    resolve: {
        extensions: ['.tsx', '.ts', '.js'],
    },
    output: {
        filename: 'DomPolyfill.js',
        path: path.resolve(__dirname, 'build/polyfill'),
    },
};
