NetworkTimeoutSample
====================

DESCRIPTION
--------------------

Mini Test code for checking timeout value effects in NSURLSession.


PLATFORM
--------------------

iOS 7 and above.  You have to enable ARC.


USAGE
--------------------

1. Tap 'timeoutIntervalForRequest:5'.
`timeoutIntervalForRequest` for `NSURLSessionConfiguration`
is set to 5.  It'll be timeout though server sends
responses every 3 seconds.

2. Tap timeoutIntervalForRequest:10'.
`timeoutIntervalForRequest` for `NSURLSessionConfiguration`
is set to 10.  It'll be success without timeout.


AUTHOR
--------------------

MIYOKAWA, Nobuyoshi

* E-Mail: n-miyo@tempus.org
* Twitter: nmiyo
* Blog: http://blogger.tempus.org/


COPYRIGHT
--------------------

MIT LICENSE

Copyright (c) 2013 MIYOKAWA, Nobuyoshi (http://www.tempus.org/)

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
