t = (-50: 1: 50);
delta_t = (t ~= 0) * 0 + (t == 0) * 1;
stem(t-10, delta_t);
