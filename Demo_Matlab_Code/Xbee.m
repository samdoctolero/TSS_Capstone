classdef Xbee < handle
    %UNTITLED3 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        address
        port  
        Object
    end
    
    methods
        function this = Xbee(port)
            this.port = port;
        end
        
        function complete = initialize(this)
            this.Object = serial(strcat('COM',num2str(this.port)));
            set(this.Object,'BaudRate',9600);
            set(this.Object,'DataBits',8);
            set(this.Object,'Parity','None');
            set(this.Object,'StopBits',1);
            try
                fopen(this.Object);
                complete = true;
            catch ex
                complete = false;
            end
        end
        
        function [str] = getEcho(this)
            str = fscanf(this.Object,'%s');
            %fprintf('echo: %s\n',echo);
        end
    end
    
end

