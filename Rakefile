$: << "lib"

require 'rubygems'
require 'hoe'
require 'rake/extensiontask'
require 'vplay/version'

Hoe.plugins.delete :rubyforge
Hoe.plugin :minitest
Hoe.plugin :gemspec # `gem install hoe-gemspec`
Hoe.plugin :git     # `gem install hoe-git`


Hoe.spec 'vplay' do
  developer 'Joey Wendt', 'joey@joeywendt.com'

  self.version        = Vplay::Version
  self.readme_file    = 'README.md'
  self.history_file   = 'CHANGELOG.md'
  self.spec_extras    = { 
    :extensions => ["ext/vplay/extconf.rb"],
    :required_ruby_version => '>= 1.9.3'
  }

  self.extra_dev_deps << ['rake-compiler', '>= 0.8.1']
  self.extra_dev_deps << ['hoe', '>= 3.0.6']

  Rake::ExtensionTask.new('vplay', spec) do |ext|
    ext.lib_dir = File.join('lib', 'vplay')
  end
end

Rake::Task[:test].prerequisites << :compile
