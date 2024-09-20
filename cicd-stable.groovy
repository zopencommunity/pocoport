node('linux')
{
  stage ('Poll') {
    checkout([
      $class: 'GitSCM',
      branches: [[name: '*/main']],
      doGenerateSubmoduleConfigurations: false,
      extensions: [],
      userRemoteConfigs: [[url: 'https://github.com/zopencommunity/pocoport.git']]])
  }
  stage('Build') {
    build job: 'Port-Pipeline', parameters: [string(name: 'PORT_GITHUB_REPO', value: 'https://github.com/zopencommunity/pocoport.git'), string(name: 'PORT_DESCRIPTION', value: 'A collection of C++ class libraries, conceptually similar to the Java Class Library or the .NET Framework.' ), string(name: 'BUILD_LINE', value: 'STABLE') ]
  }
}
