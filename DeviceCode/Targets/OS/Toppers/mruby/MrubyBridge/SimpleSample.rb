#
# $Id: SimpleSample.rb 1887 2012-09-14 07:26:36Z okuma-top $
#

# mruby 版 SimpleSapmle
#  Sample セルを mruby から操作する

# ブリッジセルを bridge に割り付ける
p "creating bridge"
bridge = TECS::TsSample.new( "SimpleBridge" )

# (1) sayHello を呼び出す
#	 ER  sayHello( [in]int32_t times );

times = 5
p "TEST sayHello #{times} times"
bridge.sayHello( times )

# (2) howAreYou を呼び出す
#	 ER  howAreYou( [out,string(len)]char_t *buf, [in]int32_t len );

# howoAreYou の引数を準備
len = 32
buf = TECS::CharPointer.new( len )

# howAreYou を呼び出す
p "TEST howAreYou"
bridge.howAreYou( buf, len )
print buf.to_s, "\n"
