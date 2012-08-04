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

static VALUE rb_new_media(VALUE klass, VALUE rb_vlc, VALUE rb_path)
{
    libvlc_instance_t *vlc;
    libvlc_media_t *media;

    if (!rb_obj_is_kind_of(rb_vlc, cVLC))
        rb_raise(rb_eTypeError, "Expecting a Vplay::VLC instance");
    Data_Get_Struct(rb_vlc, libvlc_instance_t, vlc);

    Check_Type(rb_path, T_STRING);

    VALUE file_exists = rb_funcall(rb_const_get(rb_cObject, rb_intern("File")), rb_intern("exists?"), 1, rb_path);

    if(!file_exists)
        rb_raise(rb_eException, "No such file.");

    media = libvlc_media_new_path(vlc, StringValueCStr(rb_path));

    return Data_Wrap_Struct(klass, 0, libvlc_media_release, media);
}

/*
 *  Gets Ruby strings or Qnil from libvlc media meta attributes.
 *  @private
 */
static VALUE get_meta_data(libvlc_media_t *media, libvlc_meta_t libvlc_meta_attribute)
{
    char *data;

    data = libvlc_media_get_meta(media, libvlc_meta_attribute);

    if(data)
        return rb_str_new2(data);
    
    return Qnil;
}

/*
 *  call-seq:
 *      media.meta -> Hash attributes
 *
 *  Gets a hash of the media's meta data.
 *
 *  If an attribute is empty, it will return nil.
 *
 *     media = Vplay::Media.new(vlc, path)
 *     media.meta
 *     # => {:title=>"I'm Different", :album=>"Portal 2: Songs to Test By" ...}
 *
 *     Avaiable Meta Attributes:
 *
 *     title
 *     artist
 *     genre
 *     copyright
 *     album
 *     track_number
 *     description
 *     rating
 *     date
 *     setting
 *     url
 *     language
 *     now_playing
 *     publisher
 *     encoded_by
 *     artwork_url
 *     track_id
 *     
 *  @return [Hash] of string attributes.
 */
static VALUE rb_get_meta(VALUE self)
{
    libvlc_media_t *media;
    VALUE hash;

    Data_Get_Struct(self, libvlc_media_t, media);

    if(!libvlc_media_is_parsed(media))
        libvlc_media_parse(media);

    hash = rb_hash_new();

    rb_hash_aset(hash, ID2SYM(rb_intern("title")),        get_meta_data(media, libvlc_meta_Title));
    rb_hash_aset(hash, ID2SYM(rb_intern("artist")),       get_meta_data(media, libvlc_meta_Artist));
    rb_hash_aset(hash, ID2SYM(rb_intern("genre")),        get_meta_data(media, libvlc_meta_Genre));
    rb_hash_aset(hash, ID2SYM(rb_intern("copyright")),    get_meta_data(media, libvlc_meta_Copyright));
    rb_hash_aset(hash, ID2SYM(rb_intern("album")),        get_meta_data(media, libvlc_meta_Album));
    rb_hash_aset(hash, ID2SYM(rb_intern("track_number")), get_meta_data(media, libvlc_meta_TrackNumber));
    rb_hash_aset(hash, ID2SYM(rb_intern("description")),  get_meta_data(media, libvlc_meta_Description));
    rb_hash_aset(hash, ID2SYM(rb_intern("rating")),       get_meta_data(media, libvlc_meta_Rating));
    rb_hash_aset(hash, ID2SYM(rb_intern("date")),         get_meta_data(media, libvlc_meta_Date));
    rb_hash_aset(hash, ID2SYM(rb_intern("setting")),      get_meta_data(media, libvlc_meta_Setting));
    rb_hash_aset(hash, ID2SYM(rb_intern("url")),          get_meta_data(media, libvlc_meta_URL));
    rb_hash_aset(hash, ID2SYM(rb_intern("language")),     get_meta_data(media, libvlc_meta_Language));
    rb_hash_aset(hash, ID2SYM(rb_intern("now_playing")),  get_meta_data(media, libvlc_meta_NowPlaying));
    rb_hash_aset(hash, ID2SYM(rb_intern("publisher")),    get_meta_data(media, libvlc_meta_Publisher));
    rb_hash_aset(hash, ID2SYM(rb_intern("encoded_by")),   get_meta_data(media, libvlc_meta_EncodedBy));
    rb_hash_aset(hash, ID2SYM(rb_intern("artwork_url")),  get_meta_data(media, libvlc_meta_ArtworkURL));
    rb_hash_aset(hash, ID2SYM(rb_intern("track_id")),     get_meta_data(media, libvlc_meta_TrackID));

    return hash;
}

void Init_vplay_media()
{
    cMedia = rb_define_class_under(mVplay, "Media", rb_cObject);
    
    rb_define_singleton_method(cMedia, "new", rb_new_media, 2);

    rb_define_method(cMedia, "meta", rb_get_meta, 0);
}