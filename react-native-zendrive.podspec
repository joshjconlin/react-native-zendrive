require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "react-native-zendrive"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.description  = <<-DESC
                  react-native-zendrive
                   DESC
  s.homepage     = "https://github.com/joshjconlin/react-native-zendrive"
  s.license      = "MIT"
  # s.license    = { :type => "MIT", :file => "FILE_LICENSE" }
  s.authors      = { "Josh Conlin, Cade Beller" => "josh@moderncodesolutions.com" }
  s.platform     = :ios, "7.0"
  s.source       = { :git => "https://github.com/joshjconlin/react-native-zendrive.git", :tag => "#{s.version}" }

  s.source_files = "ios/**/*.{h,m,swift}"
  s.requires_arc = true

  s.dependency "React"

  # s.dependency "..."
end

