static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name = "viewport" content = "width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0">
<title>Bomb Squad Game Clock</title>
<style>
"body { background-color: #93B874; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }"
</style>
<script>
var websock;
function start() {
  websock = new WebSocket('ws://' + window.location.hostname + ':81/');
  websock.onopen = function(evt) { console.log('websock open'); };
  websock.onclose = function(evt) { console.log('websock close'); };
  websock.onerror = function(evt) { console.log(evt); };
  websock.onmessage = function(evt) {
    console.log(evt);
    var e = document.getElementById('clockstatus');
    if (evt.data === 'run') {
      e.style.color = 'green';
    }
    else if (evt.data === 'pause') {
      e.style.color = 'red';
    }
    else if (evt.data === 'reset') {
      e.style.color = 'black';
    }
    else if (evt.data === 'plus') {
      e.style.color = 'blue';
    }
    else if (evt.data === 'minus') {
      e.style.color = 'orange';
    }
    else {
      console.log('unknown event');
    }
  };
}
function buttonclick(e) {
  websock.send(e.id);
}
</script>
</head>
<body onload="javascript:start();">
<h1><span style="color: #0000ff;">Bomb Squad Game Clock Controller</span></h1>
<div id="clockstatus"><b>CLOCK</b></div>
<div> </div>
<button id="run"  type="button" onclick="buttonclick(this);">Start</button> 
<button id="pause" type="button" onclick="buttonclick(this);">Stop</button>
<button id="reset" type="button" onclick="buttonclick(this);">Reset</button>
<button id="plus" type="button" onclick="buttonclick(this);">+</button>
<button id="minus" type="button" onclick="buttonclick(this);">-</button>
</body>
</html>
)rawliteral";
