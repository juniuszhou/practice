$path="/home/junizhou/bin/AD/mea_list";
open(FILE,"$path");
@meas=<FILE>;
@meas= sort(@meas);
foreach $item (@meas)
{
chomp($item);
print $item;

print "\n";
}
close(FILE);
exit();

