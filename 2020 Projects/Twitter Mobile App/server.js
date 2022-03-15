require('dotenv').config();
const express = require('express');
const app = express();
const port = process.env.PORT || 5000;
const path = require('path');
const bodyParser = require('body-parser');
const twit = require('twit');
const bcrypt = require("bcrypt");
const saltRounds = 10;

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended:false}));

// Server is up and running
app.listen(port, () => console.log(`Listening on port ${port}`));

// Login Request
//bcrypt.hash('', saltRounds, function (err,hash){console.log(hash)})
app.post('/login',function(req,res){
    console.log(req.body)
    bcrypt.compare(req.body.pw, process.env.PASS, function (err, result) {
        if (result) {
            res.json({auth: true});
        } else {
            res.json({auth: false});
        }
    })
})

// Twitter Requests
var T = new twit({
  consumer_key:         process.env.C_KEY,
  consumer_secret:      process.env.C_SECRET,
  access_token:         process.env.A_TOKEN,
  access_token_secret:  process.env.A_SECRET,
  timeout_ms:           60*1000,  // optional HTTP request timeout to apply to all requests.
  strictSSL:            true,     // optional - requires SSL certificates to be valid.
})

// Get user data based on screen name
app.post('/screen', (req,res) => {
  T.get('users/lookup', {screen_name: req.body.handle}, function(err, data, response) {res.json(data)})
})

// Get list of twitter ids where user is following.
app.post('/friends_id', (req,res) => {
  T.get('friends/ids', {screen_name: req.body.handle, cursor: req.body.cursor, count: 5000}, function(err, data, response) {res.json(data)})
})

// Get user data based on string of twitter ids
app.post('/user_info', (req,res) => {
  T.get('users/lookup', {user_id: req.body.user_string}, function(err, data, response) {res.json(data)})
})

// Get user timeline
app.post('/tweets', (req,res) => {
  T.get('statuses/user_timeline', {user_id: req.body.user_id, count: 50}, function(err, data, response) {res.json(data)})
})
