function acomodador(h)
h(1) = subplot(3,2,1);
h(2) = subplot(3,2,2);
h(3) = subplot(3,2,3);
h(4) = subplot(3,2,4);
h(5) = subplot(3,2,5); % the last (odd) axes
pos = get(h,'Position');
new = mean(cellfun(@(v)v(1),pos(1:2)));
set(h(5),'Position',[new,pos{end}(2:end)])
end