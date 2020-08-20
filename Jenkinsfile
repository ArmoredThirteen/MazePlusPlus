pipeline {
	agent any
	
	options {
		buildDiscarder(logRotator(numToKeepStr:'3'))
		disableConcurrentBuilds()
	}
	
	stages {
		stage('Build')
			steps
				stageBuild()
		/*stage('Test') {
			steps {
				stageTest()
			}
		}
		stage('Deploy') {
			steps {
				stageDeploy()
			}
		}*/
	}
	
	post {
		always {
			postAlwaysCleanup()
		}
	}
}


void stageBuild() {
	sh "ls"
	sh "g++ main.cpp Backtrack.cpp"
	sh "ls"
}

void stageTest() {
	
}

void stageDeploy() {
	// PHP pages
	sh "scp ./index.php jenkinsbuild@174.138.54.72:/var/www/html/MazeGen"
	sh "scp ./mazeImage.php jenkinsbuild@174.138.54.72:/var/www/html/MazeGen"
	sh "scp ./backtrack.php jenkinsbuild@174.138.54.72:/var/www/html/MazeGen"
	
	// C++ code
	sh "scp ./a.out jenkinsbuild@174.138.54.72:/var/www/html/MazeGen"
}

void postAlwaysCleanup() {
	echo "Cleanup"
	cleanWs()
}


boolean isMaster(){
	return BRANCH_NAME.equals("master")
}


//TODO: Why no work?
/*void scpToMazeGen(String filename) {
	sh 'scp ${filename} jenkinsbuild@174.138.54.72:/var/www/html/MazeGen'
}*/