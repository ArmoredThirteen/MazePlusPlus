pipeline {
	agent any
	
	options {
		buildDiscarder(logRotator(numToKeepStr:'3'))
		disableConcurrentBuilds()
	}
	
	stages {
		stage('Build') {
			steps {
				echo "Build"
				sh "ls"
				sh "g++ main.cpp Backtrack.cpp"
				sh "ls"
			}
		}
		
		/*stage('Test') {
			steps {
				echo "Test"
			}
		}*/
		
		stage('Deploy') {
			steps {
				script {
					echo "Deploy"
					
					withCredentials([usernamePassword(credentialsId: 'GameSaveJenkinsBuild', passwordVariable: 'pass', usernameVariable: 'user')]) {
						
						/*def remote = [:]
						remote.name = '174.138.54.72'
						remote.host = '174.138.54.72'
						remote.user = $user
						remote.password = $pass
						remote.allowAnyHosts = true
						sshCommand remote: remote, command: "ls"*/
					}
				}
			}
		}
	}
	
	post {
		always {
			echo "Cleanup"
			cleanWs()
			//TODO: Ensure started scripts are stopped
			//TODO: Unmount container or whatever
		}
	}
}