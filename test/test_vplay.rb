require 'minitest/autorun'
require 'vplay'

class TestVplay < MiniTest::Unit::TestCase
  def test_sanity
    Vplay::Player.new
  end
end
