perl printIP.pl -mainhost 10 -secondaryIP 10
#!/opt/nokianms/bin/perl
use DBI;
use strict;
use Getopt::Long;
my $mainHost;
my $secondIP;
my $boolError = GetOptions("mainhost=s" => \$mainHost,"secondaryIP=s" => \$secondIP);
my $strUserName = "omc";
my $strPassword = "omc";
my $strError;
my $dbHandle = undef;
my $sql;
my $sth;
my $result;
my $a1;
my $a2;
$a1=$mainHost;
$dbHandle = DBI->connect( "dbi:Oracle:",$strUserName,$strPassword);
$sql = "SELECT CNE_IP_ADDRESS,CNE_LATEST_TIME FROM IP_TIMESTAMP_TABLE WHERE CNE_IP_ADDRESS=\'$mainHost\' OR C
NE_IP_ADDRESS=\'$secondIP\' ORDER BY CNE_LATEST_TIME DESC";
$sth = $dbHandle->prepare( $sql );
$result = $sth->execute();
$sth->bind_columns(undef,\$a1,\$a2);
$sth->fetch();
$sth->finish();
print ("$a1\n");

