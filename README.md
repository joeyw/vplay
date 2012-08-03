#  Vplay  

https://github.com/joeyw/vplay

## DESCRIPTION:

Vplay is a ruby binding for libvlc for playing files.

## REQUIREMENTS:

### OS X
[VLC](http://www.videolan.org/)  

###Ubuntu
`libvlc-dev`  

## INSTALL:

### OS X

[Install VLC](http://www.videolan.org/)

Add the following to your bash profile, because fuck us.
`export DYLD_LIBRARY_PATH=/Applications/VLC.app/Contents/MacOS/lib:$DYLD_LIBRARY_PATH`  
`gem install vplay`

### Ubuntu

`apt-get install libvlc-dev`  
`gem install vplay`

## Example

```ruby
require 'vplay'

# Kick up new VLC instance and a player for it.
vlc = Vplay::VLC.new
player = Vplay::Player.new vlc

# Load the song into the vlc instance.
media = Vplay::Media.new vlc, "/path/to/awesome.mp3"

# Set the current song for the player
player.media = media

player.play # that shit
```

## LICENSE:

Copyright (c) 2012 Joey Wendt

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
