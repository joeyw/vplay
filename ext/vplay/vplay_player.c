/*
 * The MIT License
 *
 * Copyright (c) 2012 Joey Wendt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <vplay.h>

extern VALUE cVLC;
extern VALUE cMedia;

VALUE cPlayer;

void rb_media_player_free(libvlc_media_player_t *media_player)
{
    libvlc_media_player_release(media_player);
}

static VALUE rb_new_player(VALUE klass, VALUE rb_vlc)
{
    libvlc_instance_t *vlc;
    libvlc_media_player_t *media_player;

    if (!rb_obj_is_kind_of(rb_vlc, cVLC))
        rb_raise(rb_eTypeError, "Expecting a Vplay::VLC instance");
    Data_Get_Struct(rb_vlc, libvlc_instance_t, vlc);

    media_player = libvlc_media_player_new(vlc);

    return Data_Wrap_Struct(klass, 0, &libvlc_media_player_release, media_player);
}

/*
 *  call-seq:
 *      player.media -> media or nil
 *
 *  Return the media currently loaded by the player, or +nil+ if
 *  no media is loaded.
 */
static VALUE rb_player_get_media(VALUE self)
{
    return rb_iv_get(self, "@media");
}

/*
 *  call-seq:
 *      player.media = media
 *
 *  Sets the media of +player+ to +media+.
 */
static VALUE rb_player_set_media(VALUE self, VALUE rb_media)
{
    libvlc_media_player_t *media_player;
    libvlc_media_t *media;

    Data_Get_Struct(self, libvlc_media_player_t, media_player);

    if (!rb_obj_is_kind_of(rb_media, cMedia))
        rb_raise(rb_eTypeError, "Expecting a Vplay::Media instance");
    Data_Get_Struct(rb_media, libvlc_media_t, media);

    libvlc_media_player_set_media(media_player, media);

    rb_iv_set(self, "@media", rb_media);
    return self;
}

void Init_vplay_player()
{
    cPlayer = rb_define_class_under(mVplay, "Player", rb_cObject);

    rb_define_singleton_method(cPlayer, "new", rb_new_player, 1);

    rb_define_method(cPlayer, "media", rb_player_get_media, 0);
    rb_define_method(cPlayer, "media=", rb_player_set_media, 1);
}
