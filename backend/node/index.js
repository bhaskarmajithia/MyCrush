// node wale folder se hi call krni h
var express = require('express');
var bodyParser = require('body-parser');
var app = express();
app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true }));

var exec = require('child_process').exec;

app.post('/signUp', (req, res)=>{
	console.log(req.body);
	var fbTrue = parseInt(req.body.isFbSignUp) === 1 ? true : false;
	if(fbTrue){
		var cmd = '../signUp.out true ' + req.body.emailId +' ' + req.body.name + ' ' + req.body.birthdate + ' ' + req.body.password + ' ' + req.body.linkOfProfilePicture + ' ' + req.body.contactNumber + ' ' + req.body.gender + ' ' + req.body.interestedIn + ' ' + req.body.salt + ' ' + req.body.isNumberVisible + ' ' + req.body.fbId + ' ' + req.body.friendList;

	}
	else {

		var cmd = '../signUp.out false ' + req.body.emailId +' ' + req.body.name + ' ' + req.body.birthdate + ' ' + req.body.password + ' ' + req.body.linkOfProfilePicture + ' ' + req.body.contactNumber + ' ' + req.body.gender + ' ' + req.body.interestedIn + ' ' + req.body.salt + ' ' + req.body.isNumberVisible;
	}


	exec(cmd, function(error, stdout, stderr) {
	  // command output is in stdout
	  console.log("error: ", error);
	  console.log("Output: ", stdout);
	  console.log("STDERR: ", stderr);
	  if(error){
	  	res.sendStatus(500);
	  }
	  else{
		res.send(stdout);
	  }

	});
});
app.post('/getSalt', function(req, res){
	var cmd = '../getSalt.out ' + req.body.emailId;
	exec(cmd, function(error, stdout, stderr) {
	  // command output is in stdout
	  console.log("error: ", error);
	  console.log("Output: ", stdout);
	  console.log("STDERR: ", stderr);
	  if(error){
	  	res.sendStatus(500);
	  }
	  else{
		res.send(stdout);
	  }

	});
});

app.post('/login', function(req, res){
	var cmd = '../login.out ' + req.body.emailId + ' ' + req.body.password;
	exec(cmd, function(error, stdout, stderr) {
	  // command output is in stdout
	  console.log("error: ", error);
	  console.log("Output: ", stdout);
	  console.log("STDERR: ", stderr);
	  if(error){
	  	res.sendStatus(500);
	  }
	  else{
		res.send(stdout);
	  }

	});
});

app.post('/searchAll', function(req, res){
	var cmd = '../searchInTst.out true ' + req.body.name;
	exec(cmd, function(error, stdout, stderr) {
	  // command output is in stdout
	  console.log("error: ", error);
	  console.log("Output: ", stdout);
	  console.log("STDERR: ", stderr);
	  if(error){
	  	res.sendStatus(500);
	  }
	  else{
		res.send(stdout);
	  }

	});
});


app.post('/searchInTst', function(req, res){
	var cmd = '../searchInTst.out false ' + req.body.prefix + ' ' + req.body.numberOfPerson;
	exec(cmd, function(error, stdout, stderr) {
	  // command output is in stdout
	  console.log("error: ", error);
	  console.log("Output: ", stdout);
	  console.log("STDERR: ", stderr);
	  if(error){
	  	res.sendStatus(500);
	  }
	  else{
		res.send(stdout);
	  }

	});
});


app.post('/addEdge', function(req, res){
	var cmd = '../addEdgeInCrushGraph.out ' + req.body.start + ' ' + req.body.end;
	exec(cmd, function(error, stdout, stderr) {
	  // command output is in stdout
	  console.log("error: ", error);
	  console.log("Output: ", stdout);
	  console.log("STDERR: ", stderr);
	  if(error){
	  	res.sendStatus(500);
	  }
	  else{
		res.send(stdout);
	  }

	});
});


app.post('/removeEdge', function(req, res){
	var cmd = '../removeEdgeInGraph.out ' + req.body.start + ' ' + req.body.end;
	exec(cmd, function(error, stdout, stderr) {
	  // command output is in stdout
	  console.log("error: ", error);
	  console.log("Output: ", stdout);
	  console.log("STDERR: ", stderr);
	  if(error){
	  	res.sendStatus(500);
	  }
	  else{
		res.send(stdout);
	  }

	});
});

app.post('/displayCrushList', function(req, res){
	var cmd = '../displayCrushList.out ' + req.body.start;
	exec(cmd, function(error, stdout, stderr) {
	  // command output is in stdout
	  console.log("error: ", error);
	  console.log("Output: ", stdout);
	  console.log("STDERR: ", stderr);
	  if(error){
	  	res.sendStatus(500);
	  }
	  
		res.send(stdout);


	});
});


app.post('/displayMatchList', function(req, res){
	var cmd = '../displayMatchList.out ' + req.body.start;
	exec(cmd, function(error, stdout, stderr) {
	  // command output is in stdout
	  console.log("error: ", error);
	  console.log("Output: ", stdout);
	  console.log("STDERR: ", stderr);
	  if(error){
	  	res.sendStatus(500);
	  }
	  else{
		res.send(stdout);
	  }

	});
});


app.listen(3000);