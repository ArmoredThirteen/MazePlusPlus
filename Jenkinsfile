pipeline {
	agent any
	
	options {
		buildDiscarder(logRotator(numToKeepStr:'3'))
		disableConcurrentBuilds()
	}
	
	stages {
		stage('Build') {
			steps {
				echo BRANCH_NAME.equals ("Jenkins")
				echo BRANCH_NAME.equals ("Master")
				/*echo "Build"
				sh "ls"
				sh "g++ main.cpp Backtrack.cpp"
				sh "ls"*/
			}
		}
		
		/*stage('Test') {
			steps {
				echo "Test"
			}
		}*/
		
		/*stage('Deploy') {
			steps {
				script {
					echo "Deploy"
					
					// PHP pages
					sh "scp ./index.php jenkinsbuild@174.138.54.72:/var/www/html/MazeGen"
					sh "scp ./mazeImage.php jenkinsbuild@174.138.54.72:/var/www/html/MazeGen"
					sh "scp ./backtrack.php jenkinsbuild@174.138.54.72:/var/www/html/MazeGen"
					
					// C++ code
					sh "scp ./a.out jenkinsbuild@174.138.54.72:/var/www/html/MazeGen"
				}
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

//TODO: Why no work?
/*void scpToMazeGen (String filename) {
	sh 'scp ${filename} jenkinsbuild@174.138.54.72:/var/www/html/MazeGen'
}*/