x = Xbee(4);
if(~x.initialize())
 disp('Error. Cannot connect to Xbee');
end

disp(x.getEcho);

delete(x.Object);