<?php
$name = $_GET['name'];
$password = $_GET['password'];
// specify the LDAP server to connect to
$conn = ldap_connect("ldap-service","389") or die("Could not connect to server");  
ldap_set_option($conn, LDAP_OPT_PROTOCOL_VERSION, 3);
// bind to the LDAP server specified above 
$r = ldap_bind($conn, "cn=admin,dc=lorenzodentis,dc=org", "admin") or die("Could not bind to server");     
// search for credentials
$result = ldap_search($conn,"dc=lorenzodentis,dc=org", "(&(uid=".$name.")(userpassword=".$password."))");
//$result = ldap_search($conn,"dc=lorenzodentis,dc=org", "(&(uid=".$name.")(userpassword=".$password."))");
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
prova
<?php
echo "dn is: ". $entry["dn"] ."<br>";
echo "first cn is: ". $entry["cn"][0] ."<br>";
echo "first email address is: ". $entry["mail"][0] ."<br>";
echo "password is: ". $entry["userpassword"][0] ."<br>";
//$certificate = $entry["usercertificate;binary"][0];
?>
</body>
</html>
