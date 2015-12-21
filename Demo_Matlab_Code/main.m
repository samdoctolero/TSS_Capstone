delete(instrfindall);
x = Xbee(5);
if(~x.initialize())
 disp('Error. Cannot connect to Xbee');
end

if (x.Object.BytesAvailable ~= 0)
    disp(x.getEcho);
end


    disp('Good');
    disp(x.sendAndReceive('AT'));

delete(x.Object);