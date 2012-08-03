require 'minitest/autorun'
require 'vplay'

class TestVplay < MiniTest::Unit::TestCase
  def setup
    @vlc = Vplay::VLC.new
    @player = Vplay::Player.new @vlc
    @media_file = File.expand_path("test/fixtures/portal2-ost-clip.mov")
    @media = Vplay::Media.new @vlc, @media_file
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
    assert_raises ArgumentError do
      Vplay::Media.new
    end

    assert_raises TypeError, 2 do
      Vplay::Media.new "", 0
    end

    assert_raises TypeError, 2 do
      Vplay::Media.new "", @media_file
    end
  end

  def test_set_player_media
    assert @player.media == nil

    @player.media = @media
    assert_equal @media, @player.media
  end

  def test_player_play
    assert @player.play == false

    @player.media = @media
    assert @player.play
  end
end
