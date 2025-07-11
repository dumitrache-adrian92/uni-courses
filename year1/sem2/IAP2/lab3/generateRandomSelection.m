function[] = generateRandomSelection(mean,disp)
% Function that generates 1000 points given in a gaussian distribution with
% a median and a dispersion
    N=1000;
    data = 1 + disp * randn(N,mean);
    figure(1);
    hist(data)
    title("histogram");
end