Substitution is specified with s. It is placed before the first forward slash surrounding the search expression. The string that will be used to replace the matching pattern is included within a second set of slashes. 
$string =~ s/apples/oranges/;  

In the above example, the expression being searched for in the variable $string is "apples". Where ever this is found, it will be replaced by "oranges". 
$string1 = "I love to eat apples all day. I can eat apples every day! Apples are yummy!";
$string1 =~ s/apples/oranges/;
print "The resulting value is : $string1 \n";  


See the example
The above will react to the first found result. To make it search/replace through the entire string, use the g option after the last forward slash. 
$string1 = "I love to eat apples all day. I can eat apples every day! Apples are yummy!";
$string1 =~ s/apples/oranges/g;
print "The resulting value is : $string1 \n";  


See the example
Keep in mind that Perl is CaSe SeNsItIvE. To get rid of the case sensitivity, use the i option after the "g". 
$string1 = "I love to eat apples all day. I can eat apples every day! Apples are yummy!";
$string1 =~ s/apples/oranges/gi;
print "The resulting value is : $string1 \n";  


See the example
The g and i option have been discussed on the previous webpage. There is one more option which is e which stands for expression. This will parse an expression to its value during the replacement action. 
$string =~ s/apples/3*3/g;  
The above example will replace any occurance of "apples" with the text "3*3". The value of 3*3 was not produced during the replace. 
$string =~ s/apples/3*3/ge;  
The above example will replace any occurances of "apples" with "9". The value of 3*3 was parsed with the expression option turned added. 


