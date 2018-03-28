%%En este documento calcularemos los valores necesarios para el modelado
%%teorico
format long g %%Incluido para ver si obteniamos mas decimales
Un = 12; %%Voltios  %La tensión a la que funciona el motor
Rm = 2.23; %% Terminal Resistance [Ohmios] %%Valor obtenido de la tabla
Lm = 2.64e-4; %% Terminal inductance [Henrios] %%Valor obtenido de la tablla
Jm = 4.14e-6; %% Rotor inertia [Kg * m^2] Valor obtenido de la tabla
tm  = 1.57e-2; %% Mechanical time constant [s] 

te = Lm/Rm; %%constante de tiempo eléctrica [s]
km = 2.43e-2;%% Torque constant [N*m/A]
kb = (60/(394*2*pi)); %% Speed Constant [V*S/rad] %%En la tabla se obtenie speed constant en rpm,
%%El valor buscado es el inverso y en V*S/rad
Io = 0.058; %%no load current  [A]
no = 4660*2*pi/60; %% no load speed [rad/s]


%%Calculo constante viscosa


%Método de la constante de tiempo mecánica
Bmt = (Jm/tm) - ((kb*km)/Rm);
%Método de la corriente del motor sin carga
Bmc = (km*Io)/no;

%%Nos quedaremos con la constante de viscosidad calculada
%%con la corriente del motor sin carga
Bm = Bmc;
%%Calculo de los polos
tm2 = Jm/Bm; %%tm prima
p1 = -(1/2)*((1/te) +(1/tm2))-(1/2)*(((1/te) +(1/tm2))^(2) - 4*((km*kb)/(Jm*Lm)))^(1/2);
p2 = -(1/2)*((1/te) +(1/tm2))+(1/2)*(((1/te) +(1/tm2))^(2) - 4*((km*kb)/(Jm*Lm)))^(1/2);

%%De aquí obtenemos que |p2|<<|p1| y por tanto p2 es el polo dominante;

%%Si para el calculo del polo mediante la aproximación de la eliminación
%%de la constante eléctrica, obtenemos el siguiente polo

p3 = -(1/tm);

%%Calculo de la función de transferencia según el modelo no simplificado

Km = km/(Jm*Lm)



