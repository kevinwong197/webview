require 'find_a_port'
require 'rbwebview'
require 'sinatra/base'

ProcQueue = Queue.new

class Backend < Sinatra::Application
  set :port, FindAPort.available_port

  get '/' do
    ProcQueue << proc { Webview.set_title('ok') }
    erb (<<~ERB)
      <h1>ok</h1>
      <h2>
        <a href="/exit">exit</a>
        <a href="/a">a</a>
      </h2>
    ERB
  end

  get '/a' do
    ProcQueue << proc { Webview.set_title('ayy') }
    erb (<<~ERB)
      <h1>a</h1>
      <h2>
        <a href="/">back</a>
        <a href="/fullscreen">fullscreen</a>
        <a href="/unfullscreen">unfullscreen</a>
      </h2>
    ERB
  end

  get '/fullscreen' do
    ProcQueue << proc { Webview.set_fullscreen(1) }
    redirect back
  end

  get '/unfullscreen' do
    ProcQueue << proc { Webview.set_fullscreen(0) }
    redirect back
  end

  get '/exit' do
    ProcQueue << proc do
      Webview.exit
      Webview.terminate
    end
  end
end

Webview = Rbwebview.new('sinatra', "http://localhost:#{Backend.settings.port}")
Thread.new do
  Backend.run!
end
Webview.init
sleep(1) until Backend.settings.running?

while(Webview.loop(1) == 0) do
  sleep 0.01
  next if ProcQueue.size == 0
  command = ProcQueue.pop
  command.call
end
