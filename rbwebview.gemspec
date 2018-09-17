Gem::Specification.new do |s|
  s.name = 'rbwebview'
  s.version = '0.0.1'
  s.author = ''
  s.summary = 'ruby webview binding'
  s.files = `git ls-files`.split("\n")
  s.extensions << 'ext/rbwebview/extconf.rb'
  s.has_rdoc = false
end
