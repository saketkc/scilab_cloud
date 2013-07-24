<?php
$ch = curl_init();
$url="http://scilab-test.garudaindia.in/cloud/get_books";
$fields = array (
			"api_user" => urlencode("scilab"),
                        "api_key" => urlencode("zdFmTjX98.")
                );
$fields_string='';
foreach($fields as $key=>$value) { $fields_string .= $key.'='.$value.'&'; }
rtrim($fields_string, '&');
//set the url, number of POST vars, POST data
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch,CURLOPT_URL, $url);
curl_setopt($ch,CURLOPT_POST, count($fields));
curl_setopt($ch,CURLOPT_POSTFIELDS, $fields_string);
$result = curl_exec($ch);

$json_d = json_decode($result);
//print_r($json_d->{"response"}->{"books"});
$books = $json_d ->{'response'}->{'books'};
echo "<table><tr><td>Select Book</td><td>";
echo "<select id='books' name='books'><option value=''></option>";
foreach($books as $key=>$value) { echo  "<option value='$key'>".$value.'</option>'; }
echo "</select></td></tr></table>";
$show='';
?>
<html>
<head>
<script  src="jquery.js" type="text/javascript"></script>
<script>
$(document).ready(function(){
 $("a#single_image").fancybox();
$("#graph-dwnld").hide();
$("#books").live("change",function(){

id = $("#books").val();
//alert(id);
$.ajax({
    type: 'GET',
    url: 'get_chapters.php?id='+id,

    success: function(responseData, textStatus, jqXHR) {
        //var value = responseData.someKey;
	$("#c").html(responseData);
	$("#lc").html("Select Chapter");
    },
    error: function (responseData, textStatus, errorThrown) {
        alert('POST failed.');
    }
});
});

$("#chapter").live("change", function(){
id = $("#chapter").val();

$.ajax({
    type: 'GET',
    url: 'get_examples.php?id='+id,

    success: function(responseData, textStatus, jqXHR) {
        //var value = responseData.someKey;
	$("#e").html(responseData);
	$("#le").html("Select Example");
    },
    error: function (responseData, textStatus, errorThrown) {
        alert('POST failed.');
    }
});
}
);

$("#submit").live("click",function(){
 if ($('#graphicsmode').is(':checked')){val =1;} else{val='';}
   $("#submit").attr("value","Executing.........");
//   $("#submit").attr("disabled","disabled");	
   $.ajax({
      type: "POST",
          url: "submit.php",
          data:{code:$("#input").val(),graphicsmode:val},
          dataType: "json",
          success: function(resp ) {
		msg = resp["response"];

//		$("#submit").attr("disabled","");	
                $("#submit").attr("value","Execute");
                $("#output").val(msg["output"]);
                if (msg["graph"]!=""){
                $("#single_image").attr("href","http://scilab-test.garudaindia.in/cloud/graphs/"+msg["user_id"]+"/"+msg["graph"]+".png");
                $("#image").attr("src","http://scilab-test.garudaindia.in/cloud/graphs/"+msg["user_id"]+"/"+msg["graph"]+".png");
                $("#download").attr("href","http://scilab-test.garudaindia.in/cloud/download/"+msg["graph"]);
                $("#graph-dwnld").show();
                $("#single_image").trigger("click")  ;

}}});});
$("#example").live("change", function(){
id = $("#example").val();
folder = $("#books").val();
$.ajax({
    type: 'GET',
    url: 'get_code.php?id='+id+"&folder="+folder,

    success: function(responseData, textStatus, jqXHR) {
        //var value = responseData.someKey;
	$("#input").val(responseData);
//	$("#le").html("Select Example");
    },
    error: function (responseData, textStatus, errorThrown) {
        alert('POST failed.');
    }
});
}
);
});
</script>
    <script src="fancybox.js"></script>
    <link href="fancybox.css" rel="stylesheet">

</head>
<div id ="image" style="display:none"><a id="single_image" href=""><img id="image" src=""></a></div>

<table>
<tr><td><div id="lc"></div></td><td><div id="c"></div></td></tr>

<tr><td><div id="le"></div></td><td><div id="e"></div></td></tr>
<tr><td>Input</td><td>Output</td></tr>
<tr><td><textarea name="code" id="input" rows="20" cols="40"></textarea></td><td><textarea name="code" id="output" rows="20" cols="40"></textarea></td></tr>
<tr><td><input type="checkbox" id="graphicsmode">Enable Graphics</td></tr>
<tr><div id="graph-dwnld">Download <a id="download" href="">here</a></div></a></tr>
</table>
<br/>
<input type="button" id="submit" name="submit" value="Execute">

