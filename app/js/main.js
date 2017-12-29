var mqtt = require('mqtt')
var client  = mqtt.connect('mqtt://128.199.79.47:8083')

client.on('connect', function () {
  client.subscribe('outTopic')
})

var plant1water = document.getElementById("plant1water")
var plant2water = document.getElementById("plant2water")

client.on('message', function (topic, message) {
  // message is Buffer
  console.log(message.toString())
  plant1water.innerHTML = message.toString() + "%"
  plant2water.innerHTML = (message/2).toString() + "%"
})