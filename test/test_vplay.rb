require 'minitest/autorun'
require 'vplay'

class TestVplay < MiniTest::Unit::TestCase
  def setup
    @vlc = Vplay::VLC.new
    @player = Vplay::Player.new @vlc
  end

  def test_vlc_version
    version = Vplay::VLC.libvlc_version
    assert version =~ /[0-9]\.[0-9]\.[0-9]/
  end

  def test_vlc_player
    assert_raises TypeError do
      Vplay::Player.new "bad type"
    end

    assert_raises ArgumentError do
      Vplay::Player.new
    end
  end
end
