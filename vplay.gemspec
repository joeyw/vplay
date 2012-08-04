# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = "vplay"
  s.version = "1.0.0.20120804041237"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.authors = ["Joey Wendt"]
  s.date = "2012-08-04"
  s.description = "Vplay is a ruby binding for libvlc for playing files."
  s.email = ["joey@joeywendt.com"]
  s.extensions = ["ext/vplay/extconf.rb"]
  s.extra_rdoc_files = ["Manifest.txt"]
  s.files = [".autotest", ".gemtest", "Manifest.txt", "README.md", "CHANGELOG.md", "Rakefile", "lib/vplay.rb", "lib/vplay/version.rb", "test/test_vplay.rb", "ext/vplay/extconf.rb"]
  s.homepage = "https://github.com/joeyw/vplay"
  s.rdoc_options = ["--main", "README.md"]
  s.require_paths = ["lib"]
  s.required_ruby_version = Gem::Requirement.new(">= 1.9.3")
  s.rubyforge_project = "vplay"
  s.rubygems_version = "1.8.24"
  s.summary = "Vplay is a ruby binding for libvlc for playing files."
  s.test_files = ["test/test_vplay.rb"]

  if s.respond_to? :specification_version then
    s.specification_version = 3

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_development_dependency(%q<rdoc>, ["~> 3.10"])
      s.add_development_dependency(%q<rake-compiler>, [">= 0.8.1"])
      s.add_development_dependency(%q<hoe>, [">= 3.0.6"])
    else
      s.add_dependency(%q<rdoc>, ["~> 3.10"])
      s.add_dependency(%q<rake-compiler>, [">= 0.8.1"])
      s.add_dependency(%q<hoe>, [">= 3.0.6"])
    end
  else
    s.add_dependency(%q<rdoc>, ["~> 3.10"])
    s.add_dependency(%q<rake-compiler>, [">= 0.8.1"])
    s.add_dependency(%q<hoe>, [">= 3.0.6"])
  end
end
