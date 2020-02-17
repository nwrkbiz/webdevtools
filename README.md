Web Dev Tools
=============

Simple platform independent GUI program to ease web development.

Includes following features:
* HTTP Webserver, allows serving files via http and inspecting client HTTP requests.
* Websocket server, allows receiving and answering to text messages (useful for protocol prototyping).
* Websocket client, allows sending custom messages (useful for protocol prototyping).

All modules support TLS/SSL encryption.

## Releases

Releases are avaiable for many CPU architectures and completely statically linked. Linux releases need an X-Server to render the GUI. [Click here to download the newest release.](https://github.com/nwrkbiz/webdevtools/releases)

## Dependencies (to compile)

This program depends on Boost (tested with version 67), OpenSSL, [giri's c++ supportlib](https://github.com/nwrkbiz/Cpp-SupportLibrary), fltk and requires an C++17 compliant compiler.

## License

"THE BEER-WARE LICENSE" (Revision 42):
<giri@nwrk.biz> extended and modified this file. As long as you retain this notice you
can do whatever you want with this stuff. If we meet some day, and you think
this stuff is worth it, you can buy me a beer in return Daniel Giritzer

## About

2020, Daniel Giritzer

https://page.nwrk.biz/giri