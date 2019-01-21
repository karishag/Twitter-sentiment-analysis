var mysql = require('mysql');
var connection = mysql.createConnection({
  host: 'localhost',
  user: 'root',
  password: 'ngudbhav',
  database : 'twitter'
});

connection.connect();
console.log("Connection Complete");

module.exports = connection;