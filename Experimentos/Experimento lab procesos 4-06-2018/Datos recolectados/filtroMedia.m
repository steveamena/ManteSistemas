function Xout = filtroMedia(X,p)
n = size(X);
n = n(1);
Xout = zeros(n,1);

for i = (p:n)
    x = 0;
    for j = (i:-1:i-p+1)
        x = X(j)+x; 
    end
    Xout(i)=x/p;
end