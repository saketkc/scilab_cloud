<?php 
$ch = curl_init();
$id= $_GET['id'];
$folder = $_GET['folder'];
$fields = array (
                        "example" => urlencode($id),               
			"folder" => urlencode($folder),
			"api_user" => urlencode("scilab"),
                        "api_key" => urlencode("zdFmTjX98.")
                );
$fields_string='';
foreach($fields as $key=>$value) { $fields_string .= $key.'='.$value.'&'; }
rtrim($fields_string, '&');
$url="http://scilab-test.garudaindia.in/cloud/get_code";
//set the url, number of POST vars, POST data
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch,CURLOPT_URL, $url);
curl_setopt($ch,CURLOPT_POST, count($fields));
curl_setopt($ch,CURLOPT_POSTFIELDS, $fields_string);
//execute post
$result = curl_exec($ch);
$json_d = json_decode($result);
//print_r($json_d);
echo $json_d->{'response'}->{'data'};
//echo "<select name='chapter'>";
//foreach($json_d as $key=>$value) {  echo "<option value='$key'>".$value.'</option>'; }
//echo "</select>";


?>

