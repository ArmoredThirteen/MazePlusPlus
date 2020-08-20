pipeline {
	agent any
	
	options {
		buildDiscarder(logRotator(numToKeepStr:'3'))
		disableConcurrentBuilds()
	}
	
	stages {
		stage('Build') {steps {stageBuild() }}
		stage('Test')  {steps {stageTest()  }}
		stage('Deploy'){steps {stageDeploy()}}
	}
	
	post {always {postAlwaysCleanup()}}
}


void stageBuild() {
	sh "ls"
	sh "g++ main.cpp Backtrack.cpp"
	sh "ls"
}

void stageTest() {
	
}

void stageDeploy() {
	String[] filesToMove = [
		"./index.php",
		"./mazeImage.php",
		"./backtrack.php",
		"./a.out",
	]
	
	for (int i = 0; i < filesToMove.length; i++) {
		scpToMazeGen(filesToMove[i]);
	}
}

void postAlwaysCleanup() {
	echo "Cleanup"
	cleanWs()
}


boolean isMaster(){
	return BRANCH_NAME.equals("master")
}


void scpToMazeGen(String filename) {
	sh "scp ${filename} jenkinsbuild@174.138.54.72:/var/www/html/MazeGen"
}