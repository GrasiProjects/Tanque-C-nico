function z = inicializa(porta)
    global SerPIC
    disp('Inicializando Serial...');

    % Verifica se a porta já está aberta e fecha se necessário
    if ~isempty(instrfind)
        fclose(instrfind);
        delete(instrfind);
    end

    % Inicializa a comunicação serial com o ESP32 usando serialport
    SerPIC = serialport(porta, 115200, 'Parity', 'none', 'StopBits', 1, 'DataBits', 8);
    
    disp('--> pass 1');
    beep
    pause(1)
    
    disp('--> pass 2');
    beep
    pause(1)
    
    disp('Serial ok');
end
