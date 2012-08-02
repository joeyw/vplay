require 'minitest/autorun'
require 'vplay'

class TestVplay < MiniTest::Unit::TestCase
  def test_vlc
    vlc = Vplay::VLC.new
  end

  def test_vlc_version
    version = Vplay::VLC.libvlc_version
    assert version =~ /[0-9]\.[0-9]\.[0-9]/
  end
end
