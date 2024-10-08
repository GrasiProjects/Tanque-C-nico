function velocidade = recebe_velocidade
global SerPIC
flushinput(SerPIC);
fprintf(SerPIC,'%c','w');
ler = fscanf(SerPIC,'%s')
velocidade = str2double(ler);
  
if isnan(velocidade) %Checagem de erro
     fprintf(SerPIC,'%c','w');
     ler = fscanf(SerPIC,'%s');
     velocidade = str2double(ler);
end 

flushoutput(SerPIC);
end