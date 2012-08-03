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
    assert Vplay::Player.new(@vlc)

    assert_raises TypeError do
      Vplay::Player.new "bad type"
    end

    assert_raises ArgumentError do
      Vplay::Player.new
    end
  end

  def test_load_media_file
    path = "fixtures/portal2-ost-clip.mov"
    @media = Vplay::Media.new @vlc, path

    assert_raises ArgumentError do
      Vplay::Media.new
    end

    assert_raises TypeError, 2 do
      Vplay::Media.new "", 0
    end

    assert_raises TypeError, 2 do
      Vplay::Media.new "", path
    end
  end
end
