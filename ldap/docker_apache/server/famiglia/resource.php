<?php
$name = $_GET['name'];
$password = $_GET['password'];
$ip = $_SERVER['REMOTE_ADDR'];
if (substr($ip,0,9)!= substr($_SERVER['SERVER_ADDR'],0,9)){
	die("not connecting from localhost, ip is: " . $ip);
}
// specify the LDAP server to connect to
$conn = ldap_connect("ldap-service","389") or die("Could not connect to server");  
ldap_set_option($conn, LDAP_OPT_PROTOCOL_VERSION, 3);
// bind to the LDAP server specified above 
$r = ldap_bind($conn, "cn=admin,dc=lorenzodentis,dc=org", "admin") or die("Could not bind to server");     
// search for credentials
$result = ldap_search($conn,"ou=famiglia,dc=lorenzodentis,dc=org", "(&(uid=".$name.")(userpassword=".$password."))");
// get entry data as array
$info = ldap_get_entries($conn, $result);
if ($info["count"] == 0) {
	die("Invalid credentials");
}
$entry = $info[0];
ldap_close($conn);
?>
<html>
<head>
<title> title </title>
</head>
<body>
Certificate Info <br>
<?php
$cn = $_SERVER['SSL_CLIENT_S_DN_CN'];
$email = $_SERVER['SSL_CLIENT_S_DN_Email'];
echo "cn is: ". $cn . "<br>email is: ". $email . "<br>";
if($cn != $entry["cn"][0]){
	die("Certificate and user name does not corrisponds");
}
if($email != $entry["mail"][0]){
	die("Certificate and email does not corrisponds");
}
?>
<br>ldap Info <br>
<?php
echo "dn is: ". $entry["dn"] ."<br>";
echo "first cn is: ". $entry["cn"][0] ."<br>";
echo "first email address is: ". $entry["mail"][0] ."<br>";
echo "password is: ". $entry["userpassword"][0] ."<br>";
//$certificate = $entry["usercertificate;binary"][0];
echo "ip is " . $ip;
?>

</body>
</html>
