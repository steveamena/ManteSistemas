function h = graficador(Tiempo,Aceleracion,p,Nombre)
    T = Tiempo(625:1404);
    A = Aceleracion(625:1404);
    h(p) = subplot(2,2,p);
    plot(T,A);
    xlabel('Tiempo (s)');
    ylabel('Aceleración (g)');
    grid on;
    title(Nombre);
    
    
end