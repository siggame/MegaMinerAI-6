Orbited.settings.port = 9000;
Orbited.settings.hostname = "localhost";
TCPSocket = Orbited.TCPSocket;

var add_message = function(payload){
    var child = document.getElementById("child");
    document.getElementById("messages").removeChild(child)
    var message1 = payload.toString();
    message_div = document.createElement("div");
    message_div.innerHTML = message1;
    message_div.setAttribute("id", "child")
    document.getElementById("messages").appendChild(message_div);
};

stomp = null;

$(document).ready(function(){
	stomp = new STOMPClient();
	stomp.onopen = function(){
	};
	stomp.onclose = function(c){
	    alert('Lost Connection, Code: ' + c);
	};
	stomp.onerror = function(error){
	    alert("Error: " + error);
	};
	stomp.onerrorframe = function(frame){
	    alert("Error: " + frame.body);
	};
	stomp.onconnectedframe = function(){
	    stomp.subscribe("/queue/bar");
	};
	stomp.onmessageframe = function(frame){
	    add_message(frame.body);
	};
	stomp.connect('localhost', 61613, 'guest', 'guest');
    });

function onclose(e) {
    alert("boop");
    stomp.unsubscribe("/queue/bar");
    stomp.disconnect();
}

window.onbeforeunload = onclose;

$("#disconnect").click(function(){
        stomp.unsubscribe("/queue/bar");
        stomp.disconnect();
	//    var message_text = document.getElementById("shout_text").value;
	//    stomp.send(message_text, '/queue/foo', '')
	//    <!-- $.ajax({ -->
	//    <!--     type:'POST', -->
	//    <!--     url:'http://192.168.1.11/xhr/', -->
	//    <!--     data:{ -->
	//    <!--     'message':message_text, -->
	//    <!--     }, -->
	//    <!-- }); -->
    });
