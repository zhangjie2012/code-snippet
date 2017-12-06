/*
 * 开发环境: webpack
 * 线上环境: PROD_ENV=1 webpack
 */

var webpack = require('webpack');

var PROD = JSON.parse(process.env.PROD_ENV || '0');

const path = require('path');

module.exports = {
  entry: './entry.js',

  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: PROD ? 'v1.0.0.js' : 'dev.bundle.js'
  },

  plugins: PROD ? [
    new webpack.optimize.UglifyJsPlugin({
      compress: { warnings: false }
    })
  ] : [],

  module: {
    loaders: [
      { test: /\.css$/, loader: 'style-loader!css-loader' }
    ]
  }
};
