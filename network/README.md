rapid-framework
===================
__The framework for rapid software development.__

## network

The network library is a module designed to provide a starting place for managing protocol-based network interfaces in
your applications. It provides default implementations for managing multiple network interfaces, interface
sessions/connections, packet definitions, packet serialization/codec & more. Being built on top of [Wangle](https://github.com/facebook/wangle),
an existing non-blocking I/O (NIO) networking library developed by Facebook, we have a well built async-first backend ready
to power this module & your applications.

## Compiling

The network library compiles as a stand-alone shared library that you can link against, or you can optionally
statically compile it directly into your application. Once you have all the required dependencies installed it's as simple
as running cmake and installing the resulting build into your system paths. You can then link against the `rapid::network`
library target in your CMakeLists.txt.

## License Information

The content of this repo is & always will be licensed under the [Unlicense](http://unlicense.org/).

> This is free and unencumbered software released into the public domain.
> 
> Anyone is free to copy, modify, publish, use, compile, sell, or
> distribute this software, either in source code form or as a compiled
> binary, for any purpose, commercial or non-commercial, and by any
> means.

__A full copy of the license is available [here](../LICENSE).__

#

__A [NxtLvL Software Solutions](https://github.com/NxtLvLSoftware) product.__