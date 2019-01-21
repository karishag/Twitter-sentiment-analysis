var twit = require('twit');
var T = new twit({
  consumer_key:         '-----KEY-----',
  consumer_secret:      '----Secret----',
  access_token:         '-----Token-----',
  access_token_secret:  '----token-secret----'
});
var i = 0;
var c = 0;
var emojis = [':-)', ':-(', ':)', ':–D', ';-)', ':-p', ':-()', ':-/', ':-*', ':-@', ':-X', '0:-)', ':\'-(', ':–|'];
var tweets = [];
getTweets(i);
function getTweets(i){
  if(i === 14){
    return;
  }
  T.get('search/tweets', {q: emojis[i]+' since:2011-07-11', count: 20}, function(error, data, response){
    var j = 0;
    if(data['statuses']!==undefined){
      while(j<data['statuses'].length)
      {
        if(data['statuses'][j]['user'].lang === 'en'){
          /*const db = require('./db.js');
          db.query('insert into tweets values(?, ?, ?)', [c, data['statuses'][j++].text, emojis[i]], function(error, results){
            if(error){
              console.log(error);
            }
            else{
              c++;*/
              //console.log(data['statuses'][j++].text);
              /*tweets[c++] = data['statuses'][j].text;*/
              tweets.push(data['statuses'][j].text);
              //c++;
    //          console.log(c);
              j++;
              console.log(i);
              console.log(j);
              //console.log(tweets[c++]);
              if(i>10){
                printTweets();
              }
  /*            console.log(j);*/
              /*console.log(tweets[c++]);*/
          /*  }
          });*/
        }
        else{
          j++;
        }
      }
    }
    getTweets(i+1);
  });
}
function printTweets(){
for(var k in tweets){
  /*console.log(tweets[k]);*/
  const db = require('./db.js');
  db.query('insert into tweets values(?, ?, ?)', [c, tweets[k], emojis[i]], function(error, results){
    if(error) {
      console.log(error);
    }
    else{
      console.log(tweets[k])
    }
  });
}
}
