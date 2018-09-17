require 'mkmf'

# `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`
if RUBY_PLATFORM =~ /cygwin|mingw/
  $CFLAGS += " -DWEBVIEW_WINAPI=1 "
  $LDFLAGS += " -lole32 -lcomctl32 -loleaut32 -luuid -mwindows "
elsif RUBY_PLATFORM =~ /darwin/
  $CFLAGS += " -DWEBVIEW_COCOA=1 "
  $LDFLAGS += " -framework WebKit "
else
  $CFLAGS += " -DWEBVIEW_GTK=1 #{`pkg-config --cflags gtk+-3.0 webkit2gtk-4.0`.chomp} "
  $LDFLAGS += " #{`pkg-config --libs gtk+-3.0 webkit2gtk-4.0`.chomp} "
end

create_makefile 'rbwebview/rbwebview'