/*******************************************************************************
 * Sketch name: HTML code for webpage as string literal
 * Description: htmlCode.h file used in Listing 25-5
 * Created :    October 2018
 * Author:      Neil Cameron
 * Book:        Applied Arduino: Comprehensive Projects for Everyday Electronics
 * Chapter :    Chapter 25 - Wi-Fi communication
 ******************************************************************************/

R"(
<!DOCTYPE html>
<html>
<head>
<title>Arduino Applied</title>
<style> body {font-family: Arial}
 .button {padding: 15px 15px; font-size: 20px}
 .button:focus {background-color: lime}
</style>
</head>
<body>
<h1>Arduino Applied</h1>
<span style='font-size: 20px'>LED</span>
<form action='/' method='post'>
<input type='submit' class='button' name='LED' value='ON'>
<span class='checkmark'></span>&emsp;
<input type='submit' class='button' name='LED' value='OFF'}>
<span class='checkmark'></span>
</form>
</body>
</html>
)"
