<?php

$ch = curl_init();
$code = $_POST['code'];
$graphics=($_POST['graphicsmode']);

$fields = array (
			"graphicsmode" => urlencode($graphics),
			"scilab_code" => urlencode($code),
			"api_user" => "scilab",
			"externaluser" => urlencode("3"),
			"api_key" => urlencode("zdFmTjX98.")
		);
$fields_string='';
foreach($fields as $key=>$value) { $fields_string .= $key.'='.$value.'&'; }
rtrim($fields_string, '&');
$url="http://scilab-test.garudaindia.in/cloud/scilab_evaluate";
//set the url, number of POST vars, POST data
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch,CURLOPT_URL, $url);
curl_setopt($ch,CURLOPT_POST, count($fields));
curl_setopt($ch,CURLOPT_POSTFIELDS, $fields_string);
//execute post
$result = curl_exec($ch);
echo $result;
//$json_d = json_decode($result);
//close connection
#$show = $json_d->{'output'};
//curl_close($ch);
//echo $show;

?>
