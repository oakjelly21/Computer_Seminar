%clf;
t = -1*pi:0.01:pi;
rho = (1+0.9*cos(8*t)).*(1+0.1*cos(24*t)).*(0.9+0.05*cos(200*t)).*(1+sin(t));
polar(t,rho,'g--')
title ("DEVIL'S LETTUCE");
print -deps img.eps