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

extern VALUE mVplay;
extern VALUE cVLC;

VALUE cMedia;

void rb_media_free(void *media)
{
    libvlc_media_release(media);
}

static VALUE rb_new_media(VALUE klass, VALUE rb_vlc, VALUE rb_path)
{
    libvlc_instance_t *vlc;
    libvlc_media_t *media;

    if (!rb_obj_is_kind_of(rb_vlc, cVLC))
        rb_raise(rb_eTypeError, "Expecting a Vplay::VLC instance");
    Data_Get_Struct(rb_vlc, libvlc_instance_t, vlc);

    Check_Type(rb_path, T_STRING);

    media = libvlc_media_new_path(vlc, StringValueCStr(rb_path));

    return Data_Wrap_Struct(klass, 0, libvlc_media_release, media);
}

void Init_vplay_media()
{
    cMedia = rb_define_class_under(mVplay, "Media", rb_cObject);

    rb_define_singleton_method(cMedia, "new", rb_new_media, 2);
}