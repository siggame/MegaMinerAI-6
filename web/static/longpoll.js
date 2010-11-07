function addmsg(type, msg){
    /* Simple helper to add a div.
       type is the name of a CSS class (old/new/error).
       msg is the contents of the div */
    $("#messages").append("<div class='msg " + type +"'>" + msg +"</div>" );
}
function add_message(type, payload){
    var child = document.getElementById("child");
    document.getElementById("messages").removeChild(child)
    var message1 = payload.toString();
    message_div = document.createElement("div");
    message_div.innerHTML = message1;
    message_div.setAttribute("id", "child")
    document.getElementById("messages").appendChild(message_div);
};

function success_function (data){ 
    callback("new", data); 
    setTimeout( 'waitForMsg()', 3000 );
}

function error_function(XMLHttpRequest, textStatus, errorThrown){
    callback("error", textStatus + " (" + errorThrown + ")");
    setTimeout('waitForMsg()', "15000"); /* (15 seconds) */
}

function waitForMsg(){
    /* This requests the url "msgsrv.php"
       When it complete (or errors)*/
    $.ajax({ 
	    type: "GET", 
		data: my_data,
		url: callback_url,	
		async: true, /* If set to non-async, browser shows page as "Loading.."*/
		cache: false,
		timeout:50000, /* Timeout in ms */
		success: success_function,
		error: error_function,
		}
	);
};

$(document).ready(function(){
        waitForMsg(); /* Start the inital request */
    });

my_data={};