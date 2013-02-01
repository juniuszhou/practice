#create link to database and print the result of "SELECT"
#!/opt/nokianms/bin/perl
#use strict;
use DBI;
use strict;
    my $strUserName = "omc";
    my $strPassword = "omc";
	my $strError;
	my $dbHandle = undef;
    $dbHandle = DBI->connect( "dbi:Oracle:",$strUserName,$strPassword);

    if (!$dbHandle)
      {
      $strError = "CRITICAL ERROR: Unable to connect to database, "; 
      print "$strError\n";
}
      else 
      {
      	print "ok\n";
      }
      
print ("Etload Metadata \n");
 for ($i = 1; $i <=7; $i++)
 {
  if ($i==1) {$ss_name = "reppco";}
  if ($i==2) {$ss_name = "pcobgp";}
  if ($i==3) {$ss_name = "pcodhc";}
  if ($i==4) {$ss_name = "pcofwp";}
  if ($i==5) {$ss_name = "pcogne";}
  if ($i==6) {$ss_name = "pcogns";}
  if ($i==7) {$ss_name = "pcoisw";}

print ("\n P_MeasuredObjectType table \n");
$sql = "SELECT ID,OWNER,NAME,IS_MANAGED FROM P_MeasuredObjectType WHERE OWNER = \'$ss_name\'";
	$sth = $dbHandle->prepare( $sql );	
	$result = $sth->execute();
	$sth->bind_columns(undef,\$a1,\$a2,\$a3,\$a4);
	
	while( $sth->fetch() ) {
	print ("$ss_name,$a1,$a2,$a3,$a4\n");
	}
	$sth->finish();   