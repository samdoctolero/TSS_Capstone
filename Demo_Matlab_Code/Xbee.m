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
            set(this.Object,'BaudRate',57600);
            set(this.Object,'DataBits',8);
            set(this.Object,'Parity','None');
            set(this.Object,'StopBits',1);
            set(this.Object,'Terminator','CR/LF');
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
        
        function error = setATmode(this)
            try
                %fwrite(this.Object,sprintf('%x','+++'));
                fwrite(this.Object,strcat(sprintf('+++'),'0D'));
                %this.Object.atCommand('+++');
                error = false;
            catch ex
                error = true;
                disp('Error on set AT');
            end
        end
        
        function rx = sendAndReceive(this,cmd)
            if(~this.setATmode())
                fwrite(this.Object,strcat(sprintf('%x',cmd),'0D'));
                pause(1);
                if(this.Object.BytesAvailable > 0)
                    rx = fread(this.Object);
                else
                    rx = '';
                    disp('No Return');
                end
            else
                rx = '';
            end

        end
    end
    
end

