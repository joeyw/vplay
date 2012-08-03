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

VALUE cVLC;

void rb_libvlc_free(void *vlc)
{
    libvlc_release(vlc);
}

static VALUE rb_libvlc_new(VALUE klass)
{
    libvlc_instance_t *vlc;

    vlc = libvlc_new(0, NULL);
    return Data_Wrap_Struct(klass, NULL, rb_libvlc_free, vlc);
}

/*
 *  call-seq:
 *      Vplay::VLC.libvlc_version -> libvlc version string
 *
 *  Get the libvlc version the gem is using.
 *
 *      Vplay::VLC.libvlc_version
 *      #=> "2.0.3 Twoflower"
 */
static VALUE rb_libvlc_version(VALUE self)
{
    return rb_str_new2(libvlc_get_version());
}

void Init_vplay_vlc()
{
    cVLC = rb_define_class_under(mVplay, "VLC", rb_cObject);

    rb_define_singleton_method(cVLC, "new", rb_libvlc_new, 0);
    rb_define_singleton_method(cVLC, "libvlc_version", rb_libvlc_version, 0);
}
