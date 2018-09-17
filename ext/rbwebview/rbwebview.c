#include "ruby.h"
#define WEBVIEW_IMPLEMENTATION
#include "webview.h"

VALUE rbwebview_open(int argc, VALUE *argv, VALUE self)
{
  VALUE title, url, width, height, resizable;
  rb_scan_args(argc, argv, "05", &title, &url, &width, &height, &resizable);

  if (NIL_P(title))
    title = rb_str_new2("Rbwebview");
  if (NIL_P(url))
    url = rb_str_new2("https://google.com");
  if (NIL_P(width))
    width = INT2NUM(800);
  if (NIL_P(height))
    height = INT2NUM(600);
  if (NIL_P(resizable))
    resizable = INT2NUM(1);

  int ret = webview(
    RSTRING_PTR(title),
    RSTRING_PTR(url),
    NUM2INT(width),
    NUM2INT(height),
    NUM2INT(resizable));

  return INT2NUM(ret);
}

struct webview* get_webview(VALUE self)
{
  struct webview* p;
  Data_Get_Struct(self, struct webview, p);
  return p;
}

VALUE rbwebview_init(VALUE self)
{
  int ret = webview_init(get_webview(self));
  return INT2NUM(ret);
}

VALUE rbwebview_set_title(VALUE self, VALUE arg1)
{
  webview_set_title(get_webview(self), RSTRING_PTR(arg1));
  return Qnil;
}

VALUE rbwebview_terminate(VALUE self)
{
  webview_terminate(get_webview(self));
  return Qnil;
}

VALUE rbwebview_exit(VALUE self)
{
  webview_exit(get_webview(self));
  return Qnil;
}

VALUE rbwebview_loop(VALUE self, VALUE arg1)
{
  int ret = webview_loop(get_webview(self), NUM2INT(arg1));
  return INT2NUM(ret);
}

VALUE rbwebview_eval(VALUE self, VALUE arg1)
{
  int ret = webview_eval(get_webview(self), RSTRING_PTR(arg1));
  return INT2NUM(ret);
}

VALUE rbwebview_set_fullscreen(VALUE self, VALUE arg1)
{
  webview_set_fullscreen(get_webview(self), NUM2INT(arg1));
  return Qnil;
}


VALUE rbwebview_alloc(VALUE klass)
{
  struct webview *w;
  return Data_Make_Struct(klass, struct webview, NULL, free, w);
}

VALUE rbwebview_initialize(int argc, VALUE *argv, VALUE self)
{
  VALUE title, url, width, height, resizable;
  rb_scan_args(argc, argv, "05", &title, &url, &width, &height, &resizable);

  if (NIL_P(title))
    title = rb_str_new2("Rbwebview");
  if (NIL_P(url))
    url = rb_str_new2("https://google.com");
  if (NIL_P(width))
    width = INT2NUM(800);
  if (NIL_P(height))
    height = INT2NUM(600);
  if (NIL_P(resizable))
    resizable = INT2NUM(1);

  struct webview* p = get_webview(self);
  p->title = RSTRING_PTR(title);
  p->url = RSTRING_PTR(url);
  p->width = NUM2INT(width);
  p->height = NUM2INT(height);
  p->debug = 0;
  p->resizable = NUM2INT(resizable);

  return Qnil;
}

void Init_rbwebview()
{
  VALUE c = rb_define_class("Rbwebview", rb_cObject);

  rb_define_alloc_func(c, rbwebview_alloc);
  rb_define_private_method(c, "initialize", rbwebview_initialize, -1);
  rb_define_singleton_method(c, "open", rbwebview_open, -1);
  rb_define_method(c, "init", rbwebview_init, 0);
  rb_define_method(c, "loop", rbwebview_loop, 1);
  rb_define_method(c, "exit", rbwebview_exit, 0);
  rb_define_method(c, "terminate", rbwebview_terminate, 0);
  rb_define_method(c, "set_title", rbwebview_set_title, 1);
  rb_define_method(c, "eval", rbwebview_eval, 1);
  rb_define_method(c, "set_fullscreen", rbwebview_set_fullscreen, 1);
}