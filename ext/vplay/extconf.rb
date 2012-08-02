require 'mkmf'

def asplode missing
  abort "#{missing} is missing. Install VLC player from http://videolan.org " +
        "or 'apt-get install libvlc-dev'"
end

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

INCLUDEDIR = RbConfig::CONFIG['includedir']
LIBDIR     = RbConfig::CONFIG['libdir']
LIB_DIRS   = ['/opt/local/lib', '/usr/local/lib', LIBDIR, '/usr/lib']

dir_config   'vlc',
             '/Applications/VLC.app/Contents/MacOS/include',
             '/Applications/VLC.app/Contents/MacOS/lib'

find_header  'vlc/vlc.h'

find_library 'vlc',
              nil,
              '/Applications/VLC.app/Contents/MacOS/lib'

create_makefile('vplay/vplay')
