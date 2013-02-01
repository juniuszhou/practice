#!/opt/nokianms/bin/perl
use File::Copy; 
$path="C:\\Zhoujun\\";
$path_bak="C:\\Zhoujun\\bak\\";
$file_name="files";
$file_ext="txt";

$path_file_name = $path . $file_name . "." . $file_ext;

$ymd=qx(date /T);
chomp($ymd);
$ymd = substr($ymd,0,10);
$ymd =~ s/\//-/g;
$ymd .= '-';  
$hms=qx(time /T);
chomp($hms);
$hms =~ s/://;

$bak_file_name = $path_bak . $file_name . "-" . $ymd . $hms . "." . $file_ext;

copy($path_file_name,$bak_file_name);

exit();

