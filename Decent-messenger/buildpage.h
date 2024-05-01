char page[] PROGMEM = R"###(

<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, height=device-height, initial-scale=1, maximum-scale=1, user-scalable=no">
</head>
<body onload="loaded()">
  <div id="modalbox" class="hide-modal">
    <div class="head">
      Как к вам обращаться
    </div>
    <div class="main">  
        <input required type="text" class="user-icon" id="yourname" name="yourname" placeholder="Любой псевдоним">
        <input required type="text" class="region-icon" id="yourregion" name="yourregion" placeholder="Регион вашей сети">
      <script>
        if (navigator.cookieEnabled === true){
          document.write('<input type="checkbox" id="remember"><label for="remember" class="label-remember">Запомнить меня</label>');
        }
      </script>
      <input type="button" id="login" onclick="login();" value="Вход">
    </div>
  </div>
  <div class="container" id="main">
    <div id="left">
    <div id ="header-left" class="signal0">
    </div>
    <div class="searchBox">
      <input id="searchText" type="text" name="search" placeholder="Поиск...">
      <span class="search-icon"></span>
    </div>
    <div id="userlist">
    </div>
  </div>
  <div id="right">
    <div id="header-right" class="chat-name">
    </div>
    <div id="quality">
    ...
    </div>
    <div id="messages">
    </div>
    <div class="typetext">
    <div class="reply" id="reply">
      <textarea rows="1" id="comment" onkeypress="return runScript(event)"></textarea>
    </div>
      <div>
      <input class="send-button send-icon" id="send-button" type="button" onclick="postmessage()" value="">
      </div>      
    </div>
  </div>
    <a id="contacts" onclick="switchback()"></a>
  </div>

<style>
body{
  font-family: "Helvetica Neue",Helvetica,Arial,sans-serif;
  font-size: 14px;
  color: #333;
  background-color: #fff;
  margin: 0;
  touch-action: none;
  overflow:hidden !important;
  height:100%;
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg fill="%23D3D1FD" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><path d="m12 1.316c-5.901 0-10.684 4.783-10.684 10.684s4.783 10.684 10.684 10.684 10.684-4.783 10.684-10.684c-.012-5.896-4.788-10.672-10.683-10.684h-.001zm0 22.297c-6.414 0-11.613-5.199-11.613-11.613s5.199-11.613 11.613-11.613 11.613 5.199 11.613 11.613v.015c0 6.405-5.192 11.597-11.597 11.597-.005 0-.011 0-.016 0h.001z"/><path d="m12 24c-6.614-.034-11.966-5.386-12-11.997v-.003c.034-6.614 5.386-11.966 11.997-12h.003c6.614.034 11.966 5.386 12 11.997v.003c-.034 6.614-5.386 11.966-11.997 12zm0-23.226c-6.2 0-11.226 5.026-11.226 11.226s5.026 11.226 11.226 11.226 11.226-5.026 11.226-11.226c-.004-6.198-5.028-11.221-11.225-11.226zm0 22.297c-6.114 0-11.071-4.957-11.071-11.071s4.957-11.071 11.071-11.071c6.122.02 11.084 4.955 11.148 11.065v.006c-.064 6.115-5.027 11.051-11.146 11.071zm0-21.368c-5.687 0-10.297 4.61-10.297 10.297s4.61 10.297 10.297 10.297 10.297-4.61 10.297-10.297c-.026-5.676-4.62-10.271-10.294-10.297h-.002z"/><path d="m9.677 9.91c0 1.154-.936 2.09-2.09 2.09s-2.09-.936-2.09-2.09c0-.003 0-.006 0-.009 0-1.15.932-2.082 2.082-2.082h.009.009c1.15 0 2.082.932 2.082 2.082v.009z"/><path d="m18.581 9.91v.009c0 1.15-.932 2.082-2.082 2.082-.003 0-.006 0-.009 0-1.154 0-2.09-.936-2.09-2.09s.936-2.09 2.09-2.09c1.145.023 2.067.945 2.09 2.088v.002z"/><path d="m7.355 18.581c-.228-.007-.416-.169-.464-.384l-.001-.003c-.002-.015-.003-.032-.003-.049 0-.097.03-.188.081-.262l-.001.002c.087-.094.189-.172.304-.229l.006-.003 9.832-2.168c.015-.002.032-.003.049-.003.097 0 .188.03.262.081l-.002-.001c.094.087.172.189.229.304l.003.006c.01.035.016.075.016.117 0 .202-.136.373-.322.424l-.003.001-9.91 2.168h-.077z"/><path d="m7.355 18.968c-.01 0-.021.001-.032.001-.369 0-.676-.265-.741-.615l-.001-.005c-.018-.065-.029-.139-.029-.215 0-.149.039-.288.108-.408l-.002.004c.145-.168.326-.3.533-.384l.009-.003 9.832-2.245c.065-.018.139-.029.215-.029.149 0 .288.039.408.108l-.004-.002c.168.145.3.326.384.533l.003.009c.016.061.025.13.025.202 0 .392-.273.719-.639.804l-.006.001-9.91 2.245zm9.91-3.097-9.91 2.245-.077.077.077.077 9.91-2.245c0-.077.077-.077 0-.155z"/></svg>');
  background-position:center;
  background-size:45%;
  background-repeat: no-repeat;
}
#modalbox{
  width: 230px;
  height: 230px;
  border: 1px solid #ccc;
  border-radius: 5px;
  background: #fff;
  overflow: hidden;
  position: absolute;
  top: calc(20% + 1000px);
  left: calc(50% - 115px);
  z-index: 2;
}
#modalbox:before{
  content:"";
  display:block;
  position:fixed;
  top:0;
  left:0;
  width:100%;
  height:100%;
  background:#000;
  opacity:.85;
  z-index:-1;
}
.hide-modal:before{
  opacity:0 !important;
  visibility:hidden;
  transition: visibility 1s, opacity 0.5s linear;
}
#modalbox .head{
  background: #dddddd;
  margin: 0;
  padding: 12px 0 0 20px;
  height: 28px;
  font-size:16px;
}
#modalbox .main{
  width: 100%;
  height: 100%;
  margin: 0;
  padding: 10px;
  background: #fafafa;
}
.hide-modal{
  height: 0px !important;
  border: none !important;
  visibility: hidden !important;
  transition: border 0.3s, visibility 0.4s, height 0.3s linear;
}
#yourname, #yourregion{
  width: 90%;
  resize: none;
  overflow: hidden;
  outline: none;
  text-indent: 5px;
  display: block;
  float: left;
  height: 34px;
  font-size: 14px;
  color: #555;
  background-color: #fff;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-shadow: inset 0 1px 1px rgb(0 0 0 / 8%);
  transition: border-color ease-in-out .15s,box-shadow ease-in-out .15s;
  background-position: 5px 5px;
  background-size: 22px;
  background-repeat: no-repeat;
  padding: 5px 5px 5px 26px !important;
  margin: 5px 10px 0 0;
}
#login{
  border: none;
  width: 100px;
  height: 38px;
  background-color: #4ed23a;
  border-radius: 6px;
  background-size: 24px;
  background-repeat: no-repeat;
  background-position: 60px 50%;
  padding: 0px 14px;
  text-align: left;
  font-size: 16px;
  color: #FFF;
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M15 4H18C19.1046 4 20 4.89543 20 6V18C20 19.1046 19.1046 20 18 20H15M11 16L15 12M15 12L11 8M15 12H3" stroke="%23FFFFFF" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/></svg>');
}
#remember{
  width: 20px;
  height: 20px;
  transition: all ease .2s;
  margin: 5px 0 10px 0;
}
.label-remember{
  font-size: 18px;
  margin: 0 0 0 10px;
  top: -2px;
  position: relative;
}
.reload-icon{
  background-image: url(data:image/svg+xml,<svg fill="%23777777" viewBox="0 0 24 24" xmlns="http://www.w3.org/2000/svg"><path d="M1,12A11,11,0,0,1,17.882,2.7l1.411-1.41A1,1,0,0,1,21,2V6a1,1,0,0,1-1,1H16a1,1,0,0,1-.707-1.707l1.128-1.128A8.994,8.994,0,0,0,3,12a1,1,0,0,1-2,0Zm21-1a1,1,0,0,0-1,1,9.01,9.01,0,0,1-9,9,8.9,8.9,0,0,1-4.42-1.166l1.127-1.127A1,1,0,0,0,8,17H4a1,1,0,0,0-1,1v4a1,1,0,0,0,.617.924A.987.987,0,0,0,4,23a1,1,0,0,0,.707-.293L6.118,21.3A10.891,10.891,0,0,0,12,23,11.013,11.013,0,0,0,23,12,1,1,0,0,0,22,11Z"/></svg>);
}
.search-icon{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M15.7955 15.8111L21 21M18 10.5C18 14.6421 14.6421 18 10.5 18C6.35786 18 3 14.6421 3 10.5C3 6.35786 6.35786 3 10.5 3C14.6421 3 18 6.35786 18 10.5Z" stroke="%23555555" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>');
  position: absolute;
  top: 16px;
  right: 18px;
  display: block;
  width: 20px;
  height: 20px;
  line-height: 34px;
  text-align: center;
  pointer-events: none;
}
.user-icon{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M5 21C5 17.134 8.13401 14 12 14C15.866 14 19 17.134 19 21M16 7C16 9.20914 14.2091 11 12 11C9.79086 11 8 9.20914 8 7C8 4.79086 9.79086 3 12 3C14.2091 3 16 4.79086 16 7Z" stroke="%23888888" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>');
}
.region-icon{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M5.7 15C4.03377 15.6353 3 16.5205 3 17.4997C3 19.4329 7.02944 21 12 21C16.9706 21 21 19.4329 21 17.4997C21 16.5205 19.9662 15.6353 18.3 15M12 9H12.01M18 9C18 13.0637 13.5 15 12 18C10.5 15 6 13.0637 6 9C6 5.68629 8.68629 3 12 3C15.3137 3 18 5.68629 18 9ZM13 9C13 9.55228 12.5523 10 12 10C11.4477 10 11 9.55228 11 9C11 8.44772 11.4477 8 12 8C12.5523 8 13 8.44772 13 9Z" stroke="%23888888" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>');
}
.group-icon{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M8 10.5H16" stroke="%23279500" stroke-width="2" stroke-linecap="round"/><path d="M8 14H13.5" stroke="%23279500" stroke-width="2" stroke-linecap="round"/><path d="M17 3.33782C15.5291 2.48697 13.8214 2 12 2C6.47715 2 2 6.47715 2 12C2 13.5997 2.37562 15.1116 3.04346 16.4525C3.22094 16.8088 3.28001 17.2161 3.17712 17.6006L2.58151 19.8267C2.32295 20.793 3.20701 21.677 4.17335 21.4185L6.39939 20.8229C6.78393 20.72 7.19121 20.7791 7.54753 20.9565C8.88837 21.6244 10.4003 22 12 22C17.5228 22 22 17.5228 22 12C22 10.1786 21.513 8.47087 20.6622 7" stroke="%23279500" stroke-width="2" stroke-linecap="round"/></svg>');
  color: #279500 !important;
}
.signal0{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"><svg viewBox="0 0 76 76" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" baseProfile="full" enable-background="new 0 0 76.00 76.00" xml:space="preserve"><path fill="%23000000" fill-opacity="0.1" stroke-width="0.2" stroke-linejoin="round" d="M 19,57L 19,51L 25,51L 25,57L 19,57 Z M 57,19L 57,57L 51,57L 51,19L 57,19 Z M 49,27L 49,57L 43,57L 43,27L 49,27 Z M 41,35L 41,57L 35,57L 35,35L 41,35 Z M 33,44L 33,57L 27,57L 27,44L 33,44 Z "/></svg>');
}
.signal1{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"><svg viewBox="0 0 76 76" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" baseProfile="full" enable-background="new 0 0 76.00 76.00" xml:space="preserve"><path fill="%23000000" fill-opacity="1" stroke-width="0.2" stroke-linejoin="round" d="M 19,57L 19,51L 25,51L 25,57L 19,57 Z "/><path fill="%23000000" fill-opacity="0.1" stroke-width="0.2" stroke-linejoin="round" d="M 57,19L 57,57L 51,57L 51,19L 57,19 Z M 49,27L 49,57L 43,57L 43,27L 49,27 Z M 41,35L 41,57L 35,57L 35,35L 41,35 Z M 33,44L 33,57L 27,57L 27,44L 33,44 Z "/></svg>');
}
.signal2{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"><svg viewBox="0 0 76 76" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" baseProfile="full" enable-background="new 0 0 76.00 76.00" xml:space="preserve"><path fill="%23000000" fill-opacity="0.1" stroke-width="0.2" stroke-linejoin="round" d="M 57,19L 57,57L 51,57L 51,19L 57,19 Z M 49,27L 49,57L 43,57L 43,27L 49,27 Z M 41,35L 41,57L 35,57L 35,35L 41,35 Z "/><path fill="%23000000" fill-opacity="1" stroke-width="0.2" stroke-linejoin="round" d="M 19,57L 19,51L 25,51L 25,57L 19,57 Z M 33,44L 33,57L 27,57L 27,44L 33,44 Z "/></svg>');
}
.signal3{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"><svg viewBox="0 0 76 76" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" baseProfile="full" enable-background="new 0 0 76.00 76.00" xml:space="preserve"><path fill="%23000000" fill-opacity="0.1" stroke-width="0.2" stroke-linejoin="round" d="M 57,19L 57,57L 51,57L 51,19L 57,19 Z M 49,27L 49,57L 43,57L 43,27L 49,27 Z "/><path fill="%23000000" fill-opacity="1" stroke-width="0.2" stroke-linejoin="round" d="M 33,44L 33,57L 27,57L 27,44L 33,44 Z M 19,57L 19,51L 25,51L 25,57L 19,57 Z M 41,35L 41,57L 35,57L 35,35L 41,35 Z "/></svg>');
}
.signal4{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"><svg viewBox="0 0 76 76" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" baseProfile="full" enable-background="new 0 0 76.00 76.00" xml:space="preserve"><path fill="%23000000" fill-opacity="1" stroke-width="0.2" stroke-linejoin="round" d="M 41,35L 41,57L 35,57L 35,35L 41,35 Z M 33,44L 33,57L 27,57L 27,44L 33,44 Z M 19,57L 19,51L 25,51L 25,57L 19,57 Z M 49,27L 49,57L 43,57L 43,27L 49,27 Z "/><path fill="%23000000" fill-opacity="0.1" stroke-width="0.2" stroke-linejoin="round" d="M 57,19L 57,57L 51,57L 51,19L 57,19 Z "/></svg>');
}
.signal5{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"><svg viewBox="0 0 76 76" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" baseProfile="full" enable-background="new 0 0 76.00 76.00" xml:space="preserve"><path fill="%23000000" fill-opacity="1" stroke-width="0.2" stroke-linejoin="round" d="M 41,35L 41,57L 35,57L 35,35L 41,35 Z M 33,44L 33,57L 27,57L 27,44L 33,44 Z M 19,57L 19,51L 25,51L 25,57L 19,57 Z M 57,19L 57,57L 51,57L 51,19L 57,19 Z M 49,27L 49,57L 43,57L 43,27L 49,27 Z "/></svg>');
}
.send-icon{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path fill-rule="evenodd" clip-rule="evenodd" d="M19.2111 2.06722L3.70001 5.94499C1.63843 6.46039 1.38108 9.28612 3.31563 10.1655L8.09467 12.3378C9.07447 12.7831 10.1351 12.944 11.1658 12.8342C11.056 13.8649 11.2168 14.9255 11.6622 15.9053L13.8345 20.6843C14.7139 22.6189 17.5396 22.3615 18.055 20.3L21.9327 4.78886C22.3437 3.14517 20.8548 1.6563 19.2111 2.06722ZM8.92228 10.517C9.85936 10.943 10.9082 10.9755 11.8474 10.6424C12.2024 10.5165 12.5417 10.3383 12.8534 10.1094C12.8968 10.0775 12.9397 10.0446 12.982 10.0108L15.2708 8.17974C15.6351 7.88831 16.1117 8.36491 15.8202 8.7292L13.9892 11.018C13.9553 11.0603 13.9225 11.1032 13.8906 11.1466C13.6617 11.4583 13.4835 11.7976 13.3576 12.1526C13.0244 13.0918 13.057 14.1406 13.4829 15.0777L15.6552 19.8567C15.751 20.0673 16.0586 20.0393 16.1147 19.8149L19.9925 4.30379C20.0372 4.12485 19.8751 3.96277 19.6962 4.00751L4.18509 7.88528C3.96065 7.94138 3.93264 8.249 4.14324 8.34473L8.92228 10.517Z" fill="%23FFFFFF"/></svg>');
}
.cloud-xmark{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M10 11L14 15M14 11L10 15M8.4 19C5.41766 19 3 16.6044 3 13.6493C3 11.2001 4.8 8.9375 7.5 8.5C8.34694 6.48637 10.3514 5 12.6893 5C15.684 5 18.1317 7.32251 18.3 10.25C19.8893 10.9449 21 12.6503 21 14.4969C21 16.9839 18.9853 19 16.5 19L8.4 19Z" stroke="%23000000" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>');
}
.cloud-slash{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M18.5221 18.5208C17.9141 18.8274 17.2272 19 16.5 19L8.4 19C5.41766 19 3 16.6044 3 13.6493C3 11.2001 4.8 8.9375 7.5 8.5C7.59659 8.27034 7.70825 8.04754 7.83373 7.83303M10.9021 5.30015C11.4635 5.10615 12.0645 5 12.6893 5C15.684 5 18.1317 7.32251 18.3 10.25C19.8893 10.9449 21 12.6503 21 14.4969C21 14.7799 20.9739 15.0568 20.924 15.3253M3 3L21 21" stroke="%23000000" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>');
}
.cloud-down{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M12 9.5V15.5M12 15.5L10 13.5M12 15.5L14 13.5M8.4 19C5.41766 19 3 16.6044 3 13.6493C3 11.2001 4.8 8.9375 7.5 8.5C8.34694 6.48637 10.3514 5 12.6893 5C15.684 5 18.1317 7.32251 18.3 10.25C19.8893 10.9449 21 12.6503 21 14.4969C21 16.9839 18.9853 19 16.5 19L8.4 19Z" stroke="%23000000" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>');
}
.cloud-exclamation{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M12 9.5V12.5M12 15.5H12.01M8.4 19C5.41766 19 3 16.6044 3 13.6493C3 11.2001 4.8 8.9375 7.5 8.5C8.34694 6.48637 10.3514 5 12.6893 5C15.684 5 18.1317 7.32251 18.3 10.25C19.8893 10.9449 21 12.6503 21 14.4969C21 16.9839 18.9853 19 16.5 19L8.4 19Z" stroke="%23000000" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>');
}
.container{
  overflow:hidden;
  position: relative;
  height: 100%;
  margin: auto;
  padding: 0;
  box-shadow: 0 1px 1px 0 rgb(0 0 0 / 6%), 0 2px 5px 0 rgb(0 0 0 / 20%);
  width:88%;
  top: 1000px;
}
#left{
  width: 33.333%;
  background-color: #eee;
  margin: 0;
  padding: 0;
  float: left;
  height: 100%;
  position: relative;
  left: 0%;
}
.sending{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 0 100 100" preserveAspectRatio="xMidYMid"><circle cx="28" cy="75" r="11" fill="%23999999"><animate attributeName="fill-opacity" repeatCount="indefinite" dur="2s" values="0;1;1" keyTimes="0;0.2;1" begin="0s"></animate></circle><path d="M28 47A28 28 0 0 1 56 75" fill="none" stroke="%23999999" stroke-width="10"><animate attributeName="stroke-opacity" repeatCount="indefinite" dur="2s" values="0;1;1" keyTimes="0;0.2;1" begin="0.2s"></animate></path><path d="M28 25A50 50 0 0 1 78 75" fill="none" stroke="%23999999" stroke-width="10"><animate attributeName="stroke-opacity" repeatCount="indefinite" dur="2s" values="0;1;1" keyTimes="0;0.2;1" begin="0.4s"></animate></path></svg>');
  background-position: top 16px right 60px !important;
  background-repeat: no-repeat;
  background-size: 26px !important;
}
#header-left{
  padding: 10px 0 10px 0;
  line-height: 48px;
  font-size: 16px;
  margin: 0;
  height: 40px;
  background-size: 34px;
  background-repeat: no-repeat;
  background-position: 100% 15px;
  width:100%;
}
#header-left span{
  padding: 0 0 0 22px;
}
.searchBox{
  position:relative;
  padding: 10px;
  height: 40px;
  background-color: #fbfbfb;
}
#searchText{
  display: block;
  width: 100%;
  height: 34px;
  padding: 6px 45px 6px 12px;
  font-size: 14px;
  color: #555;
  background-color: #fff;
  background-image: none;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-shadow: inset 0 1px 1px rgb(0 0 0 / 8%);
  transition: border-color ease-in-out .15s,box-shadow ease-in-out .15s;
}
#searchText:focus {
  outline: none;
  border: none;
  box-shadow: none;
}
#header-left span:before{
  content: "";
  padding: 0;
  margin: 0 0;
  position: relative;
  right: -15px;
  top: 6px;
  width: 28px;
  height: 28px;
  display: block;
  float: left;
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 192 192" xmlns="http://www.w3.org/2000/svg" fill="none"><path fill="%23000000" fill-rule="evenodd" d="M63 155.478a67.799 67.799 0 0 1-3.556-2.121 6.001 6.001 0 0 0-4.376-.833l-19.36 3.768 3.768-19.36a6 6 0 0 0-.833-4.376 64.77 64.77 0 0 1-.351-.556H24.535a79.45 79.45 0 0 0 2.714 4.941l-3.887 19.971c-1.355 6.961 4.765 13.081 11.726 11.726l19.971-3.887A79.315 79.315 0 0 0 63 168.898v-13.42Z" clip-rule="evenodd"/><path fill="%23000000" fill-rule="evenodd" d="M152.569 39.431a80.396 80.396 0 0 0-12.112-9.958 6 6 0 0 0-6.678 9.97 68.336 68.336 0 0 1 10.304 8.474 68.342 68.342 0 0 1 8.474 10.304 6 6 0 1 0 9.97-6.677 80.339 80.339 0 0 0-9.958-12.112Zm-43.295-10.13a6 6 0 1 0 2.331-11.772 80.41 80.41 0 0 0-31.21 0 6 6 0 0 0 2.33 11.771 68.405 68.405 0 0 1 26.549 0Zm65.197 51.094a6 6 0 1 0-11.771 2.33 68.432 68.432 0 0 1 0 26.549 6 6 0 1 0 11.771 2.331 80.382 80.382 0 0 0 0-31.21Zm-11.944 60.062a6 6 0 1 0-9.97-6.678 68.317 68.317 0 0 1-8.474 10.304 68.482 68.482 0 0 1-8.779 7.422 6 6 0 0 0 6.947 9.785 80.599 80.599 0 0 0 10.318-8.721 80.378 80.378 0 0 0 9.958-12.112ZM58.221 39.443a6 6 0 0 0-6.677-9.97 80.357 80.357 0 0 0-12.112 9.959 80.49 80.49 0 0 0-8.722 10.317 6 6 0 0 0 9.785 6.947 68.495 68.495 0 0 1 7.422-8.78 68.36 68.36 0 0 1 10.304-8.473ZM30.6 77.325a6 6 0 0 0-11.543-3.283 80.32 80.32 0 0 0-2.914 26.768 6 6 0 0 0 11.978-.718A68.318 68.318 0 0 1 30.6 77.325Zm87.357 95.616a5.999 5.999 0 0 0 4.129-7.412 6 6 0 0 0-7.412-4.13 68.328 68.328 0 0 1-22.767 2.479 6 6 0 1 0-.717 11.978 80.317 80.317 0 0 0 26.767-2.915Zm-84.65-50.551a6 6 0 0 0-11.061 4.652A79.244 79.244 0 0 0 24.535 132h13.757a67.388 67.388 0 0 1-4.983-9.61Zm36.302 36.301a67.337 67.337 0 0 1-9.61-4.983v13.757a79.312 79.312 0 0 0 4.958 2.288 6 6 0 0 0 4.651-11.062Z" clip-rule="evenodd"/></svg>');
}
#header-left:before{
  content: "";
  padding: 0;
  margin: 0 0;
  position: relative;
  right: 24px;
  top: 8px;
  width: 24px;
  height: 24px;
  display: block;
  float: right;
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M18 3.70825C19.2447 5.11852 20 6.97101 20 8.9999C20 11.0288 19.2447 12.8813 18 14.2915M6 3.70825C4.75527 5.11852 4 6.97101 4 8.9999C4 11.0288 4.75527 12.8813 6 14.2915" stroke="%23000000" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/><path d="M15 6.35425C15.6224 7.05938 16 7.98563 16 9.00007C16 10.0145 15.6224 10.9408 15 11.6459M9 6.35425C8.37764 7.05938 8 7.98563 8 9.00007C8 10.0145 8.37764 10.9408 9 11.6459" stroke="%23000000" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/><path d="M12 9V20" stroke="%23000000" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>');
}
#header-right{
  padding: 20px 16px 0 56px;
  margin: 0;
  line-height: 18px;
  font-size: 20px;
  height: 40px;
  width: 100%;
  background-color: #eee;
  background-repeat: no-repeat;
  background-position: 18px 14px;
  background-size: 30px;
  color: #888;
}
#quality{
  position: absolute;
  height: 16px;
  width: 110px;
  top: 24px;
  right: 10px;
}
#userlist{
  overflow-y: auto;
  height: calc(100% - 120px);
  overflow-x: hidden;
  background: #fff;
}
#right{
  width: 66.666%;
  height: 100%;
  background: #f7f7f7;
  display: block;
  margin: 0;
  padding: 0;
  float: left;
  height: calc(100% - 40px);
}
.user, .group{
  display: block;
  color: #333;
  background-color: #fff;
  font-size: 16px;
  border-bottom: 1px solid #f7f7f7;
  height: 28px;
  cursor: pointer;
  background-size: 26px;
  background-repeat: no-repeat;
  background-position: 15px 14px;
  padding: 30px 0 0 50px;
  line-height: 0px;
  min-width: 200px;
  position: relative;
}
.user:before{
  display: block;
  content: "";
  width: 26px;
  height: 26px;
  position: absolute;
  top: 18px;
  right: 20%;
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M4 4L20 20" stroke="%23CCCCCC" stroke-width="2" stroke-linecap="round"/><path fill-rule="evenodd" clip-rule="evenodd" d="M6.22308 5.63732C4.19212 6.89322 2.60069 8.79137 1.73175 11.0474C1.49567 11.6604 1.49567 12.3396 1.73175 12.9526C3.31889 17.0733 7.31641 20 12 20C14.422 20 16.6606 19.2173 18.4773 17.8915L17.042 16.4562C15.6033 17.4309 13.8678 18 12 18C8.17084 18 4.89784 15.6083 3.5981 12.2337C3.54022 12.0835 3.54022 11.9165 3.5981 11.7663C4.36731 9.76914 5.82766 8.11625 7.6854 7.09964L6.22308 5.63732ZM9.47955 8.89379C8.5768 9.6272 7.99997 10.7462 7.99997 12C7.99997 14.2091 9.79083 16 12 16C13.2537 16 14.3728 15.4232 15.1062 14.5204L13.6766 13.0908C13.3197 13.6382 12.7021 14 12 14C10.8954 14 9.99997 13.1046 9.99997 12C9.99997 11.2979 10.3618 10.6802 10.9091 10.3234L9.47955 8.89379ZM15.9627 12.5485L11.4515 8.03729C11.6308 8.0127 11.8139 8 12 8C14.2091 8 16 9.79086 16 12C16 12.1861 15.9873 12.3692 15.9627 12.5485ZM18.5678 15.1536C19.3538 14.3151 19.9812 13.3259 20.4018 12.2337C20.4597 12.0835 20.4597 11.9165 20.4018 11.7663C19.1021 8.39172 15.8291 6 12 6C11.2082 6 10.4402 6.10226 9.70851 6.29433L8.11855 4.70437C9.32541 4.24913 10.6335 4 12 4C16.6835 4 20.681 6.92668 22.2682 11.0474C22.5043 11.6604 22.5043 12.3396 22.2682 12.9526C21.7464 14.3074 20.964 15.5331 19.9824 16.5682L18.5678 15.1536Z" fill="%23CCCCCC"/></svg>');
  transition: all 1s ease;
}
.online:before{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M21.335 11.4069L22.2682 11.0474L21.335 11.4069ZM21.335 12.5932L20.4018 12.2337L21.335 12.5932ZM2.66492 11.4068L1.73175 11.0474L2.66492 11.4068ZM2.66492 12.5932L1.73175 12.9526L2.66492 12.5932ZM3.5981 11.7663C4.89784 8.39171 8.17084 6 12 6V4C7.31641 4 3.31889 6.92667 1.73175 11.0474L3.5981 11.7663ZM12 6C15.8291 6 19.1021 8.39172 20.4018 11.7663L22.2682 11.0474C20.681 6.92668 16.6835 4 12 4V6ZM20.4018 12.2337C19.1021 15.6083 15.8291 18 12 18V20C16.6835 20 20.681 17.0733 22.2682 12.9526L20.4018 12.2337ZM12 18C8.17084 18 4.89784 15.6083 3.5981 12.2337L1.73175 12.9526C3.31889 17.0733 7.31641 20 12 20V18ZM20.4018 11.7663C20.4597 11.9165 20.4597 12.0835 20.4018 12.2337L22.2682 12.9526C22.5043 12.3396 22.5043 11.6604 22.2682 11.0474L20.4018 11.7663ZM1.73175 11.0474C1.49567 11.6604 1.49567 12.3396 1.73175 12.9526L3.5981 12.2337C3.54022 12.0835 3.54022 11.9165 3.5981 11.7663L1.73175 11.0474Z" fill="%23279500"/><circle cx="12" cy="12" r="3" stroke="%23279500" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>');
  transition: all 1s ease;
}
.grouphint, .userhint{
  display: block;
  width: 100%;
  height: 11px;
  float: right;
  overflow: hidden;
  font-size: 11px;
  color: #aaa;
  margin: 0;
  padding: 0;
  line-height: 11px;
  position: relative;
  left: 110px;
  top: -32px;
  pointer-events: none;
}
.usermessagescount, .groupmessagescount{
  display: block;
  width: 18px;
  height: 18px;
  float: right;
  font-size: 10px;
  color: #FFF;
  margin: 0;
  padding: 0;
  position: relative;
  right: 16px;
  top: -46px;
  pointer-events: none;
  background:#ff3131;
  line-height: 20px;
  text-align: center;
  opacity: 0;
  transition: all .8s ease;
}
.showlabel{
  opacity: 1 !important;
}
.hidden{
  display:none;
}
.user:hover {
    background-color: #f2f2f2;
}
.group:hover {
    background-color: #f2f2f2;
}
.message-body{
  margin: 0;
  margin-top: -40px;
  padding: 0 !important;
  width: 100%;
  height: auto;
  float: left;
  position: relative;
  opacity: 0;
  margin-bottom: 40px;
  top: 40px;
}
.message-body:after {
  display: block;
  width: 26px;
  height: 26px;
  content: "";
  position: relative;
  top: -2px;
  float: right;
  right: 5px;
  z-index: 1;
  transition: all 0.5s ease;
  background-image: none;
}
.issending:after{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 0 100 100" preserveAspectRatio="xMidYMid"><circle cx="50" cy="50" r="32" stroke-width="10" stroke="%23AAAAAA" stroke-dasharray="50 50" fill="none" stroke-linecap="round"><animateTransform attributeName="transform" type="rotate" repeatCount="indefinite" dur="2s" keyTimes="0;1" values="0 50 50;360 50 50"></animateTransform></circle></svg>');
}
.delivered:after {
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path fill-rule="evenodd" clip-rule="evenodd" d="M15.4933 6.93502C15.8053 7.20743 15.8374 7.68122 15.565 7.99325L7.70786 16.9933C7.56543 17.1564 7.35943 17.25 7.14287 17.25C6.9263 17.25 6.72031 17.1564 6.57788 16.9933L3.43502 13.3933C3.16261 13.0812 3.19473 12.6074 3.50677 12.335C3.8188 12.0626 4.29259 12.0947 4.565 12.4068L7.14287 15.3596L14.435 7.00677C14.7074 6.69473 15.1812 6.66261 15.4933 6.93502Z" fill="%231C274C"/><path fill-rule="evenodd" clip-rule="evenodd" d="M20.5175 7.01946C20.8174 7.30513 20.829 7.77986 20.5433 8.07981L11.9716 17.0798C11.8201 17.2389 11.6065 17.3235 11.3872 17.3114C11.1679 17.2993 10.9649 17.1917 10.8318 17.0169L10.4035 16.4544C10.1526 16.1249 10.2163 15.6543 10.5458 15.4034C10.8289 15.1878 11.2161 15.2044 11.4787 15.4223L19.4571 7.04531C19.7428 6.74537 20.2175 6.73379 20.5175 7.01946Z" fill="%231C274C"/></svg>') !important;
}
.inthecloud:after{
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M12 9.5V15.5M12 9.5L10 11.5M12 9.5L14 11.5M8.4 19C5.41766 19 3 16.6044 3 13.6493C3 11.2001 4.8 8.9375 7.5 8.5C8.34694 6.48637 10.3514 5 12.6893 5C15.684 5 18.1317 7.32251 18.3 10.25C19.8893 10.9449 21 12.6503 21 14.4969C21 16.9839 18.9853 19 16.5 19L8.4 19Z" stroke="%23888888" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>');
}
.message-body-visible{
  opacity: 1;
  top: 0;
  margin-bottom: 40px;
  transition: opacity .8s, margin, padding, top .3s ease-out;
}
#messages{
  overflow-y: auto;
  height: calc(100% - 120px);
  padding-top: 40px;
}
.sent{
  padding: 10px 20px;
  max-width: 600px;
  margin-left: 10% !important;
}
.sent-inside{
  float:right;
  width: auto !important;
  padding: 4px 25px 12px 10px !important;
  border-radius: 10px 10px 0 10px;
  background: #dcf8c6;
  font-size: 12px;
  text-shadow: 0 1px 1px rgb(0 0 0 / 20%);
  word-wrap: break-word;
  display: inline-block;
}
.recieve{
  padding: 10px 20px;
  max-width: 600px;
}
.recieve-inside{
  float: left;
  width: auto !important;
  padding: 4px 25px 12px 10px !important;
  border-radius: 10px 10px 10px 0;
  background: #ffffff;
  font-size: 12px;
  text-shadow: 0 1px 1px rgb(0 0 0 / 20%);
  word-wrap: break-word;
  display: inline-block;
}
.message-text{
  margin: 0 !important;
  padding: 5px !important;
  word-wrap: break-word;
  font-weight: 200;
  font-size: 14px;
  padding-bottom: 0 !important;
}
.emoji{
  font-size:60px;
}
.shownick{
  color: #555;
  margin: 2px 0 2px -2px;
}
.typetext{
  background-color: #f5f1ee;
  padding: 10px 5px 10px 5px !important;
  margin: 0 !important;
  width:100%;
  height:50px;
  background-size: contain;
  background-repeat: no-repeat;
  background-position: 50% -6px;
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" viewBox="0 0 200 100" preserveAspectRatio="xMidYMid"><rect x="0" y="30" width="40" height="40" fill="%234ed23a"><animate attributeName="opacity" dur="1s" repeatCount="indefinite" calcMode="spline" keyTimes="0;0.5;1" keySplines="0.5 0 0.5 1;0.5 0 0.5 1" values="1;0.2;1" begin="-0.6"></animate></rect><rect x="50" y="30" width="40" height="40" fill="%234ed23a"><animate attributeName="opacity" dur="1s" repeatCount="indefinite" calcMode="spline" keyTimes="0;0.5;1" keySplines="0.5 0 0.5 1;0.5 0 0.5 1" values="1;0.2;1" begin="-0.4"></animate></rect><rect x="100" y="30" width="40" height="40" fill="%234ed23a"><animate attributeName="opacity" dur="1s" repeatCount="indefinite" calcMode="spline" keyTimes="0;0.5;1" keySplines="0.5 0 0.5 1;0.5 0 0.5 1" values="1;0.2;1" begin="-0.2"></animate></rect><rect x="150" y="30" width="40" height="40" fill="%234ed23a"><animate attributeName="opacity" dur="1s" repeatCount="indefinite" calcMode="spline" keyTimes="0;0.5;1" keySplines="0.5 0 0.5 1;0.5 0 0.5 1" values="1;0.2;1" begin="-1"></animate></rect></svg>');
}
.reply{
  width: 75%;
  padding: 2px 5px !important;
  float:left;
}
textarea{
  display: block;
  height: 34px;
  padding: 6px 12px;
  font-size: 14px;
  color: #555;
  background-color: #fff;
  background-image: none;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-shadow: inset 0 1px 1px rgb(0 0 0 / 8%);
  transition: border-color ease-in-out .15s,box-shadow ease-in-out .15s;
}
.reply textarea{
  width: 100%;
  resize: none;
  overflow: hidden;
  padding: 5px !important;
  outline: none;
  border: none;
  text-indent: 5px;
  box-shadow: none;
  height: 34px;
  font-size: 16px;
}
.send-button{
  border: none;
  width: 36px;
  height: 36px;
  background-color: #4ed23a;
  border-radius: 50%;
  background-size: 20px;
  background-repeat: no-repeat;
  background-position: 6px 9px;
  margin-left: 4px;
  outline: none;
}
#contacts{
  display:block;
  background-image: url('data:image/svg+xml,<%3Fxml version="1.0" encoding="utf-8"%3F><svg fill="%23FFFFFF" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 52 52" enable-background="new 0 0 52 52" xml:space="preserve"><path d="M48.6,23H15.4c-0.9,0-1.3-1.1-0.7-1.7l9.6-9.6c0.6-0.6,0.6-1.5,0-2.1l-2.2-2.2c-0.6-0.6-1.5-0.6-2.1,0L2.5,25c-0.6,0.6-0.6,1.5,0,2.1L20,44.6c0.6,0.6,1.5,0.6,2.1,0l2.1-2.1c0.6-0.6,0.6-1.5,0-2.1l-9.6-9.6C14,30.1,14.4,29,15.3,29h33.2c0.8,0,1.5-0.6,1.5-1.4v-3C50,23.8,49.4,23,48.6,23z"/></svg>');
  background-color: #0843d9;
  border-radius: 6px;
  background-size: 26px;
  background-position: center;
  background-repeat: no-repeat;
  width: 40px;
  height: 40px;
  position: absolute;
  top: 10px;
  opacity:0;
}
@media(max-width:980px){
  .container{
      top: 1000px;
      height: 100%;
      width: 100%;
  }
  #left{
    width: 100%;
  }
  #right{
    width: 100%;
    position: absolute;
    top: 0;
    left: 100%;
    transition: all .18s ease-out;
  }
  .right-visible{
    left: 0 !important;
    transition: all .2s ease-out .1s;
  }
  .contacts-visible{
    opacity: 1 !important;
    left: 10px !important;
    transition: all .2s ease-out .6s;
  }
  .chat-name{
    padding: 20px 16px 0 100px !important;
    background-position: 65px 14px !important;
  }
  #contacts{
    left: -10px;
    transition: all .1s ease-out;
  }

}
</style>
<script>
var myname="";
var myregion="";
var store = false;
var groupisonthescreen = false;
var startbyte = 0;
var newmessages;
let onlineactivity = [];
setInterval(checkonlinestatus, 2000);
var str="";
var wskt;
var wsconnected = false;
let slots = [];
var attempts = 0;
var shift = 0;

setInterval(
  () => {
    var rep = document.getElementById("reply");
    var butt = document.getElementById("send-button");
    var left = document.getElementById("left");
    if (slots.length > 5){
      rep.classList.add("hidden");
      butt.classList.add("hidden");
    } else{
      rep.classList.remove("hidden");
      butt.classList.remove("hidden");
    }    
    if (slots.length > 0){
      left.classList.add("sending");
      let tmp = slots.shift();
      wskt.send(tmp[0]);
      var tochange = document.getElementById(tmp[1]);
      if (tochange){
        tochange.classList.add("issending");
      }
    } else{
      left.classList.remove("sending");
      var messages = document.querySelectorAll('.message-body');
      for (var i = 0; i < messages.length; ++i) {
        messages[i].classList.remove("issending");
      };
      var quality = Math.floor(100 / attempts * shift / 9 * 10);
      var qlabel= document.getElementById("quality");
      qlabel.innerHTML = "Качество: "+ quality +"%";      
    }
  },
  2000
);

function init(){
  document.documentElement.scrollTop = 1000;
  document.body.scrollTop = 1000;
  wskt = new WebSocket('ws://' + window.location.hostname + ':81/');
  //wskt.binaryType = "arraybuffer";
  wskt.onmessage = function(rx){
    str=str+rx.data;
    if((myname) && (myregion)){
      processmessage();
    };
  };
  wskt.onopen = function() {
    wsconnected = true;
  };
  wskt.onclose = function(e) {
    wsconnected = false;
    str="";
    document.documentElement.scrollTop = 0;
    document.body.scrollTop = 0;
    setTimeout(function() {init();}, 1000);
  };
  wskt.onerror = function(err) {
    wskt.close();
  };
};

function adduser(name, onlinestatus){
  var unique = true;
  if (name == myname){
    unique = false;
  };
  var userlist= document.getElementById("userlist");
  const allusers = document.querySelectorAll('.user');
  for (var i = 0; i < allusers.length; ++i) {
    if (name == allusers[i].innerText){
    unique = false;
    if(onlinestatus){
      onlineactivity[i] = 30;
    };
    break;
    };
  };
  if(unique){
  let div = document.createElement('div');
    div.className = "user user-icon";
  if(onlinestatus){
    onlineactivity[allusers.length] = 30;
  };
  div.innerHTML = name;
  userlist.append(div);
  div.addEventListener ('click',  loadusermessages);  
  let usermessagescount = document.createElement('div');
  usermessagescount.className = "usermessagescount";
  userlist.append(usermessagescount);
  let divhint = document.createElement('div');
  divhint.className = "userhint";
  userlist.append(divhint);
  };
};

function addgroup(name) {
  var slicename = name.slice(1);
  var unique = true;
  var userlist= document.getElementById("userlist");
  const allgroups = document.querySelectorAll('.group');
  for (var i = 0; i < allgroups.length; ++i) {
    if (slicename == allgroups[i].innerText){
    unique = false;
    break;
    };
  };
  if(unique){
  let div = document.createElement('div');
    div.className = "group group-icon";
  div.innerHTML = slicename;
  userlist.append(div);
    div.addEventListener ('click',  loadgroupmessages);
  let groupmessagescount = document.createElement('div');
  groupmessagescount.className = "groupmessagescount";
  userlist.append(groupmessagescount);
  let divhint = document.createElement('div');
  divhint.className = "grouphint";
  userlist.append(divhint);
  }; 
};
function incomingmessage(msg,id,name){
  var messages= document.getElementById("messages");
  var uniqueid = true;
  const existedmessages = document.querySelectorAll('.message-body');
  for (var i = 0; i < existedmessages.length; ++i) {
    if (existedmessages[i].id == id){
    uniqueid = false;
    break;
  };
  };
  if (uniqueid){
    const withEmojis = /\p{Extended_Pictographic}/u;
    if ((withEmojis.test(msg)) && (msg.length == 2)){
      msg="<span class='emoji'>" + msg + "</span>";
    };
    let div = document.createElement('div');
    var n = "";
    if (name){n = "<div class='shownick'>"+name+"</div>";};
    div.innerHTML = "<div class=\"recieve\"><div class=\"recieve-inside\">"
    +n
    +"<div class=\"message-text\">"
    +msg
    +"</div></div></div>";
    div.id = id;
    div.className = "message-body";
    messages.append(div);
    setTimeout(() =>{div.classList.add("message-body-visible")}, 1);
    messages.scrollTop = messages.scrollHeight;
  };
};
function outgoingmessage(msg,id,name){
  var messages= document.getElementById("messages");
  var uniqueid = true;
  const existedmessages = document.querySelectorAll('.message-body');
  for (var i = 0; i < existedmessages.length; ++i) {
    if (existedmessages[i].id == id){
    uniqueid = false;
    break;
  };
  }; 
  if (uniqueid){
    const withEmojis = /\p{Extended_Pictographic}/u;
    if ((withEmojis.test(msg)) && (msg.length == 2)){
      msg="<span class='emoji'>" + msg + "</span>";
    };
    let div = document.createElement('div');
    var n = "";
    if (name){n = "<div class='shownick'>"+name+"</div>";};
    div.innerHTML = "<div class=\"sent\"><div class=\"sent-inside\">"
    +n
    +"<div class=\"message-text\">"
    +msg
    +"</div></div></div>";
    div.id = id;
    div.className = "message-body";
    messages.append(div);
    setTimeout(() =>{div.classList.add("message-body-visible")}, 1);
    messages.scrollTop = messages.scrollHeight;
  };
};
function loadgroupmessages(e){
  const nearestlabel = e.target.nextElementSibling;
  nearestlabel.classList.remove("showlabel");
  nearestlabel.innerText = "0";
  groupisonthescreen = true;
  var username= document.getElementById("header-right");
  username.classList.add("group-icon");
  username.classList.remove("user-icon");
  username.innerHTML = e.target.innerText;
  var messages= document.getElementById("messages");
  messages.innerHTML = '';
  switchforms();
  var allmessages = str.split(/\uffff/);
  for (var index = 0; index < allmessages.length; ++index) {
    let parsedmessage = allmessages[index].split('\n');
    if (parsedmessage.length > 6){
      if((parsedmessage[0] == myname) && (parsedmessage[1] == "!"+e.target.innerText) && (parsedmessage[3] == "txt")){
      outgoingmessage(parsedmessage[6],parsedmessage[4],parsedmessage[0]);
    };
      if((parsedmessage[0] != myname) && (parsedmessage[1] == "!"+e.target.innerText) && (parsedmessage[3] == "txt")){
      incomingmessage(parsedmessage[6],parsedmessage[4],parsedmessage[0]);
    };
  };
  };
};
function loadusermessages(e){
  const nearestlabel = e.target.nextElementSibling;
  nearestlabel.classList.remove("showlabel");
  nearestlabel.innerText = "0";
  groupisonthescreen = false;
  var username= document.getElementById("header-right");
  username.classList.add("user-icon");
  username.classList.remove("group-icon");
  username.innerHTML = e.target.innerText;
  var messages= document.getElementById("messages");
  messages.innerHTML = '';
  switchforms();
  var allmessages = str.split(/\uffff/);
  for (var index = 0; index < allmessages.length; ++index) {
    let parsedmessage = allmessages[index].split('\n');
    if (parsedmessage.length > 6){
      if((parsedmessage[0] == myname) && (parsedmessage[1] == e.target.innerText) && (parsedmessage[3] == "txt")){
      outgoingmessage(parsedmessage[6],parsedmessage[4]);
    };
      if((parsedmessage[1] == myname) && (parsedmessage[0] == e.target.innerText) && (parsedmessage[3] == "txt")){
      incomingmessage(parsedmessage[6],parsedmessage[4]);
    };
    if((parsedmessage[1] == myname) && (parsedmessage[0] == e.target.innerText) && (parsedmessage[3] == "delivered")){
      let total = slots.length;
      for (let j = 0; j < total; j++){
        if (slots[0][1] == parsedmessage[6]){
          slots.shift();
          shift++;
        } else{
          break;
        };
      };
      var tochange= document.getElementById(parsedmessage[6]);
      if (tochange){
        tochange.classList.remove("issending");
        tochange.classList.remove("inthecloud");
        tochange.classList.add("delivered");
      };
	};
  };
  };
};
function switchforms(){
  var right= document.getElementById("right");
  right.classList.add("right-visible");
  var button= document.getElementById("contacts");
  button.classList.add("contacts-visible");
  setTimeout(() => {resetsearch();},1000);
};
function switchback(){
  var right= document.getElementById("right");
  right.classList.remove("right-visible");
  var button= document.getElementById("contacts");
  button.classList.remove("contacts-visible");
  groupisonthescreen = false;
  var username= document.getElementById("header-right");
  username.classList.remove("user-icon");
  username.classList.remove("group-icon");
  username.innerHTML = "";
  var messages= document.getElementById("messages");
  messages.innerHTML = '';
};
function postmessage(){
  var inp = document.getElementById("comment");
  inp.focus();
  var comment = document.getElementById("comment").value;
  if(comment){
    var displayname = "";
    const mesID = makeid();
    var reciever = document.getElementById("header-right").innerText;
    if (groupisonthescreen){
      reciever="!"+reciever;
      displayname = myname;
    }
    if (reciever){
      outgoingmessage(comment,mesID,displayname);
      send(myname,reciever,9,"txt",mesID,myregion,comment,10);
      inp.value = "";
    };
  };
};
function loaded(){
  document.documentElement.scrollTop = 1000;
  document.body.scrollTop = 1000;
  if (!myname){myname = decodeURIComponent(getCookieValue("name"));};
  if (!myregion){myregion = decodeURIComponent(getCookieValue("region"));};
  if(store){
    document.cookie = "name" + '=' + encodeURIComponent(myname)+";path=/;max-age=31556926";
    document.cookie = "region" + '=' + encodeURIComponent(myregion)+";path=/;max-age=31556926";
  };
  setTimeout(() => {enterthechat();},400);
};
function enterthechat(){
  if (wsconnected){
    if((myname) && (myregion)){
      sendonline();
      processmessage();
      setTimeout(() => {
        for (var i = 0; i < onlineactivity.length; ++i) {
          onlineactivity[i] = 0;
        };
      },2000);
      var myheader = document.getElementById("header-left");
      myheader.innerHTML = "<span>"+myname+"</span>";
    } else{
      var loginform = document.getElementById("modalbox");
      loginform.classList.remove("hide-modal");
    };
  } else{
    setTimeout(() => {enterthechat();},100);    
  }
};
document.getElementById('searchText').onkeyup = function() {
  let searchText = this.value.toLowerCase();
  let stringLength = searchText.length;
  const allgroups = document.querySelectorAll('.group');  
  const allgrouphints = document.querySelectorAll('.grouphint');
  const allusers = document.querySelectorAll('.user');
  const alluserhints = document.querySelectorAll('.userhint');
  for (var i = 0; i < allgroups.length; ++i) {
    if (searchText == allgroups[i].innerText.slice(0, stringLength).toLowerCase()){
    allgroups[i].classList.remove("hidden");
    allgrouphints[i].classList.remove("hidden");
    } else {
      allgroups[i].classList.add("hidden");
    allgrouphints[i].classList.add("hidden");
  };
  };
  for (var i = 0; i < allusers.length; ++i) {
    if (searchText == allusers[i].innerText.slice(0, stringLength).toLowerCase()){
    allusers[i].classList.remove("hidden");
    alluserhints[i].classList.remove("hidden");
    } else {
      allusers[i].classList.add("hidden");
    alluserhints[i].classList.add("hidden");
  };
  };
};

function runScript(event) {
    if (event.which == 13 || event.keyCode == 13) {
        postmessage();
        return false;
    }
    return true;
};

function resetsearch(){
  document.getElementById("searchText").value = "";
  const hidden = document.querySelectorAll('.hidden');
  for (var i = 0; i < hidden.length; ++i) {
    hidden[i].classList.remove("hidden");
  };
};

function makeid() {
    let result = '';
    const characters = '0123456789';
    const charactersLength = characters.length;
    let counter = 0;
    while (counter < 9) {
      result += characters.charAt(Math.floor(Math.random() * charactersLength));
      counter += 1;
    }
    return result;
};

function login(){
  myname = document.getElementById("yourname").value;
  myregion = document.getElementById("yourregion").value;
  store = (document.getElementById('remember').checked);
  if((myname) && (myregion)){
    var loginform = document.getElementById("modalbox");
    loginform.classList.add("hide-modal");
    loaded();
  };
};

function sendonline(){
  const mesID = makeid();
  send(myname,myname,9,"txt",mesID,myregion,"online",10);
};
function getCookieValue(a) {
    var b = document.cookie.match('(^|;)\\s*' + a + '\\s*=\\s*([^;]+)');
    return b ? b.pop() : '';
};
function send(sender,reciever,jumps,type,ID,region,text,quantity){
  var str="\uffff"+
      sender+"\n"+
      reciever+"\n"+
      jumps+"\n"+
      type+"\n"+
      ID+"\n"+
      region+"\n"+
      text+"\uffff";
  for (let i = 0; i < quantity; i++) {
    slots[slots.length] = [str, ID];
  };
  attempts = attempts + quantity;
};
function processmessage(){
  newmessages = str.substr(startbyte).split(/\uffff/);
  startbyte = str.length;
  for (var index = 0; index < newmessages.length; ++index) {
    let parsedmessage = newmessages[index].split('\n');
    if (parsedmessage.length > 6){
      if ((parsedmessage[1] == myname) && (parsedmessage[3] == "txt") && (parsedmessage[0] != myname)){
        const mesID = makeid();
        send(myname,parsedmessage[0],9,"delivered",mesID,myregion,parsedmessage[4],5)
      };
      if (parsedmessage[0].substring(0,1) == "!"){
        addgroup(parsedmessage[0]);
      } else {
        adduser(parsedmessage[0],true);
      };
      if (parsedmessage[1].substring(0,1) == "!"){
        addgroup(parsedmessage[1]);
      } else {
        adduser(parsedmessage[1],false);
      };
      const allusers = document.querySelectorAll('.user');
      const userhints = document.querySelectorAll('.userhint');
      const countuserlabels = document.querySelectorAll('.usermessagescount');
      const allgroups = document.querySelectorAll('.group');
      const grouphints = document.querySelectorAll('.grouphint');
      const countgrouplabels = document.querySelectorAll('.groupmessagescount');
      const username = document.getElementById("header-right").innerText;
      for (var l = 0; l < allusers.length; ++l) {
        if((parsedmessage[1] == myname) && (parsedmessage[0] == username) && (parsedmessage[3] == "delivered") && (parsedmessage[1].substring(0,1) != "!")){
         var tochange= document.getElementById(parsedmessage[6]);
         if (tochange){
		       tochange.classList.remove("issending");
           tochange.classList.remove("inthecloud");
           tochange.classList.add("delivered");
         };
        };
        if (
        ((parsedmessage[0] == allusers[l].innerText) || (parsedmessage[1] == allusers[l].innerText))&&
        (parsedmessage[1].substring(0,1) != "!")&&
        (parsedmessage[3] == "txt") &&
        ((parsedmessage[0] == myname) || (parsedmessage[1] == myname))
        ){
          if((parsedmessage[0] == username) && (parsedmessage[1] == myname)){
            incomingmessage(parsedmessage[6],parsedmessage[4]);
          } else if((parsedmessage[1] == username) && (parsedmessage[0] == myname)){
              outgoingmessage(parsedmessage[6],parsedmessage[4]);
          } else{     
            var thiscount = Number(countuserlabels[l].innerText);
            if (parsedmessage[0] == myname){
              thiscount = 0;
            }
            else{
              thiscount = thiscount + 1;
            };
            countuserlabels[l].innerText = thiscount;
            if(thiscount > 0){
              countuserlabels[l].classList.add("showlabel");
            }
            else{
              countuserlabels[l].classList.remove("showlabel");
            };
          };
          userhints[l].innerText = parsedmessage[6];    
          break;
        };
      };
      for (var k = 0; k < allgroups.length; ++k) {
        if ((parsedmessage[1] == "!"+allgroups[k].innerText) && (parsedmessage[3] == "txt")){
          if((parsedmessage[1] == "!"+username) && (parsedmessage[0] == myname)){
            outgoingmessage(parsedmessage[6],parsedmessage[4],parsedmessage[0]);
          } else
            if((parsedmessage[1] == "!"+username) && (parsedmessage[0] != myname)){
              incomingmessage(parsedmessage[6],parsedmessage[4],parsedmessage[0]);
            }
            else{
              var thatcount = Number(countgrouplabels[k].innerText);
              if (parsedmessage[0] == myname){
                thatcount = 0;
              }
              else{
                thatcount = thatcount + 1;
              };
              countgrouplabels[k].innerText = thatcount;
              if(thatcount > 0){
                countgrouplabels[k].classList.add("showlabel");
              }
              else{
                countgrouplabels[k].classList.remove("showlabel");
              };
            };
            grouphints[k].innerText = parsedmessage[0]+" : "+parsedmessage[6];
            break;
          };
        };
      };
      if (parsedmessage.length == 2){
      if (parsedmessage[0] == "signal"){
        var antenns = "signal" + parsedmessage[1];
        var headerforantenna = document.getElementById("header-left");
        headerforantenna.className = "";
        headerforantenna.classList.add(antenns);
      };
      if (parsedmessage[0] == "cloud"){
        var tochange = document.querySelectorAll('.message-body');
        for (var i = 0; i < tochange.length; ++i) {
          if (tochange[i].id == parsedmessage[1]){
            if (tochange[i].classList.contains("issending")){
              tochange[i].classList.remove("issending");
              tochange[i].classList.add("inthecloud");
            }
            break;
          };
        };
        let total = slots.length;
        for (let j = 0; j < total; j++){
          if (slots[0][1] == parsedmessage[1]){
            slots.shift();
            shift++;
          } else{
            break;
          };
        };
      };
    };
  };
};
function checkonlinestatus(){
  const allusers = document.querySelectorAll('.user');
  for (var i = 0; i < allusers.length; ++i) {
    if (onlineactivity[i] > 0){
      onlineactivity[i] = onlineactivity[i] - 1;
  };
  if (onlineactivity[i] > 0){
      allusers[i].classList.add("online");
  } else{
    allusers[i].classList.remove("online");
  };
  };
};
window.addEventListener('resize', () => {
  document.getElementById("main").style.height = window.visualViewport.height;
  document.documentElement.scrollTop = 1000;
  document.body.scrollTop = 1000;
});
init();
</script>
</body>
</html>

)###";
