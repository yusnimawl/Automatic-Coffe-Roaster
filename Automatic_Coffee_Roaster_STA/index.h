const char html[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html>
<head>
<title>Automatic Coffee Roaster</title>
<meta name='viewport' content='width=device-width, initial-scale=1.0'>
<link href='https://fonts.googleapis.com/css?family=Open+Sans:300,400,600' rel='stylesheet'>

<style>
html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #444444;}
body{margin: 0px;} 
h1 {font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #444444;}
.center {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 100px;
}
body{margin: 0px;} 
h1 {margin: 50px auto 30px;} 



.startbuttonlight {
  padding: 15px 25px;
  font-size: 24px;
  text-align: center;
  cursor: pointer;
  outline: none;
  color: #444444;
  background-color: orange;
  border: none;
  border-radius: 15px;
  box-shadow: 0 9px #999;
}

.startbuttonlight:hover {background-color: green}

.startbuttonlight:active {
  background-color: red;
  box-shadow: 0 5px #777;
  transform: translateY(4px);
}


.startbuttonmedium {
  padding: 15px 25px;
  font-size: 24px;
  text-align: center;
  cursor: pointer;
  outline: none;
  color: #444444;
  background-color: orange;
  border: none;
  border-radius: 15px;
  box-shadow: 0 9px #999;
}

.startbuttonmedium:hover {background-color: green}

.startbuttonmedium:active {
  background-color: red;
  box-shadow: 0 5px #777;
  transform: translateY(4px);
}

.startbuttondark {
  padding: 15px 25px;
  font-size: 24px;
  text-align: center;
  cursor: pointer;
  outline: none;
  color: #444444;
  background-color: orange;
  border: none;
  border-radius: 15px;
  box-shadow: 0 9px #999;
}

.startbuttondark:hover {background-color: green}

.startbuttondark:active {
  background-color: red;
  box-shadow: 0 5px #777;
  transform: translateY(4px);
}



.stopbutton {
  padding: 15px 25px;
  font-size: 24px;
  text-align: center;
  cursor: pointer;
  outline: none;
  color: white;
  background-color: red;
  border: none;
  border-radius: 15px;
  box-shadow: 0 9px #999;
}

.stopbutton:hover {background-color: red}

.stopbutton:active {
  background-color: green;
  box-shadow: 0 5px #777;
  transform: translateY(4px);
}

* {box-sizing: border-box}

body, html {
  height: 100%%;
  margin: 0;
  font-family: sans-serif;
}

.tablink {
  background-color: #555;
  color: white;
  float: left;
  border: none;
  outline: none;
  cursor: pointer;
  padding: 14px 16px;
  font-size: 17px;
  width: 33.333333%%;
}

.tablink:hover {
  background-color: #777;
}

.tabcontent {
  text-align: center;
  color: white;
  display: none;
  padding: 100px 20px;
  height: 35%%;
}


#Light {background-color:#B5651D;}
#Medium {background-color:#654321;}
#Dark {background-color:#261a0c;}

.side-by-side{display: table-cell;vertical-align: middle;position: relative;}
.text{font-weight: 600;font-size: 30px;width: 250px;}
.reading{font-weight: 300;font-size: 50px;padding-right: 0px;}
.temperature .reading{color: #F29C1F;}
.et .reading{color: #F29C1F;}
.statuses .reading{color: #F29C1F;}
.superscript{font-size: 17px;font-weight: 600;position: absolute;top: 10px;}
.data{padding: 0px;}
.container{display: table;margin: 0 auto;}
.icon{width:65px}
</style>
</head>
<h1>Automatic Coffee Roaster</h1>
<body>

<button class="tablink" onclick="openPage('Light', this, '#B5651D')" id="defaultOpen">Light Roast</button>
<button class="tablink" onclick="openPage('Medium', this, '#654321')">Medium Roast</button>
<button class="tablink" onclick="openPage('Dark', this, '#261a0c')">Dark Roast</button>


<div id="Light" class="tabcontent">
  <h3>Light Roast</h3>
  <p>10 Minutes Roast at 180 - 205&deg;C</p>
  <button class="startbuttonlight" onclick="startlight()">Start</button> 
  
</div>

<div id="Medium" class="tabcontent">
  <h3>Medium Roast</h3>
  <p>12 Minutes Roast at 210 - 220&deg;C</p>
  <button class="startbuttonmedium" onclick="startmedium()">Start</button>
</div>

<div id="Dark" class="tabcontent">
  <h3>Dark Roast</h3>
  <p>15 Minutes Roast at 225 - 230&deg;C</p>
  <button class="startbuttondark" onclick="startdark()">Start</button>
</div>


<div class='container'>
<div class='data statuses'>
<div class='center'>
<div class='side-by-side reading'>Status :&nbsp</div>
<div class='side-by-side reading'>
<span id="statuses">%statuses%</span>
<span class='superscript'></span></div>
</div>

<div class='container'>


<div class='data temperature'>
<div class='side-by-side icon'>
<svg enable-background='new 0 0 19.438 54.003'height=54.003px id=Layer_1 version=1.1 viewBox='0 0 19.438 54.003'width=19.438px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><g><path d='M11.976,8.82v-2h4.084V6.063C16.06,2.715,13.345,0,9.996,0H9.313C5.965,0,3.252,2.715,3.252,6.063v30.982
C1.261,38.825,0,41.403,0,44.286c0,5.367,4.351,9.718,9.719,9.718c5.368,0,9.719-4.351,9.719-9.718
c0-2.943-1.312-5.574-3.378-7.355V18.436h-3.914v-2h3.914v-2.808h-4.084v-2h4.084V8.82H11.976z M15.302,44.833
c0,3.083-2.5,5.583-5.583,5.583s-5.583-2.5-5.583-5.583c0-2.279,1.368-4.236,3.326-5.104V24.257C7.462,23.01,8.472,22,9.719,22
s2.257,1.01,2.257,2.257V39.73C13.934,40.597,15.302,42.554,15.302,44.833z'fill=#F29C21 /></g></svg>
</div>
<div class='side-by-side text'>Chamber Temperature</div>
<div class='side-by-side reading'>
<span id="temperature">%TEMPERATURE%</span>
<span class='superscript'>&deg;C</span></div>
</div>
   
<div class='data et'>
<div class='side-by-side icon'>
<svg enable-background='new 0 0 40.542 40.541'height=40.541px id=Layer_1 version=1.1 viewBox='0 0 40.542 40.541'width=40.542px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><g><path d='M34.313,20.271c0-0.552,0.447-1,1-1h5.178c-0.236-4.841-2.163-9.228-5.214-12.593l-3.425,3.424
c-0.195,0.195-0.451,0.293-0.707,0.293s-0.512-0.098-0.707-0.293c-0.391-0.391-0.391-1.023,0-1.414l3.425-3.424
c-3.375-3.059-7.776-4.987-12.634-5.215c0.015,0.067,0.041,0.13,0.041,0.202v4.687c0,0.552-0.447,1-1,1s-1-0.448-1-1V0.25
c0-0.071,0.026-0.134,0.041-0.202C14.39,0.279,9.936,2.256,6.544,5.385l3.576,3.577c0.391,0.391,0.391,1.024,0,1.414
c-0.195,0.195-0.451,0.293-0.707,0.293s-0.512-0.098-0.707-0.293L5.142,6.812c-2.98,3.348-4.858,7.682-5.092,12.459h4.804
c0.552,0,1,0.448,1,1s-0.448,1-1,1H0.05c0.525,10.728,9.362,19.271,20.22,19.271c10.857,0,19.696-8.543,20.22-19.271h-5.178
C34.76,21.271,34.313,20.823,34.313,20.271z M23.084,22.037c-0.559,1.561-2.274,2.372-3.833,1.814
c-1.561-0.557-2.373-2.272-1.815-3.833c0.372-1.041,1.263-1.737,2.277-1.928L25.2,7.202L22.497,19.05
C23.196,19.843,23.464,20.973,23.084,22.037z'fill=#F29C21 /></g></svg>
</div>
<div class='side-by-side text'>Estimated Time</div>
<div class='side-by-side reading'>
<span id="et">%et%</span>
<span class='superscript'>minutes</span></div>
</div>

<div class="center">
  <button class="stopbutton" onclick='onstop()'>STOP</button>
</div>


<script>
function startlight(){
  var xhr = new XMLHttpRequest();
  alert("Light Roast Started, Heating...");
  xhr.open("GET", "/update?light=1", true);
  xhr.send();
}
function startmedium(){
  var xhr = new XMLHttpRequest();
  alert("Medium Roast Started, Heating...");
  xhr.open("GET", "/update?med=1", true);
  xhr.send();
}
function startdark(){
  var xhr = new XMLHttpRequest();
  alert("Dark Roast Started, Heating...");
  xhr.open("GET", "/update?dark=1", true);
  xhr.send();
}
function onstop(){
  var xhr = new XMLHttpRequest();
  alert("STOPPED");
  xhr.open("GET", "/update?stop=1", true);
  xhr.send();
  }

setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("statuses").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/statuses", true);
  xhttp.send();
}, 1000 ) ;

setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 1000 ) ;

setInterval(function () {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("et").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/et", true);
  xhttp.send();
}, 1000 ) ;

function openPage(pageName,elmnt,color) {
  var i, tabcontent, tablinks;
  tabcontent = document.getElementsByClassName("tabcontent");
  for (i = 0; i < tabcontent.length; i++) {
    tabcontent[i].style.display = "none";
  }
  tablinks = document.getElementsByClassName("tablink");
  for (i = 0; i < tablinks.length; i++) {
    tablinks[i].style.backgroundColor = "";
  }
  document.getElementById(pageName).style.display = "block";
  elmnt.style.backgroundColor = color;
}

document.getElementById("defaultOpen").click();
</script>


</body>
</html> 

)rawliteral";
