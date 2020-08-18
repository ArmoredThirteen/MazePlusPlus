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
		}
		stage('Deploy') {
			steps {
				echo "Deploy"
			}
		}*/
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